
# include "config.h"
# include "version_base.h"
# include "version_tag.h"


# include  <cstdio>
# include  <iostream>
# include  <fstream>
# include  <queue>
# include  <cstring>
# include  <list>
# include  <map>
# include  <cstdlib>
# include  <algorithm>
# include  <string>
# include  <stack>
# include  <vector>

# include  "pform.h"
# include  "parse_api.h"
# include  "PGenerate.h"
# include  "netlist.h"
# include  "target.h"
# include  "compiler.h"
# include  "discipline.h"
# include  "t-dll.h"
# include "Mynetlist.h"

using namespace std;


# include  "ivl_alloc.h"

# include  "Mynetlist.h"

# include  "myBlifToV.h"

/* Count errors detected in flag processing. */
unsigned flag_errors = 0;
static unsigned long pre_process_fail_count = 0;

const char*basedir = strdup(".");

/*
 * These are the language support control flags. These support which
 * language features (the generation) to support. The generation_flag
 * is a major mode, and the gn_* flags control specific sub-features.
 */
generation_t generation_flag = GN_DEFAULT;
bool gn_icarus_misc_flag = true;
bool gn_cadence_types_flag = true;
bool gn_specify_blocks_flag = true;
bool gn_supported_assertions_flag = true;
bool gn_unsupported_assertions_flag = true;
bool gn_io_range_error_flag = true;
bool gn_strict_ca_eval_flag = false;
bool gn_strict_expr_width_flag = false;
bool gn_shared_loop_index_flag = true;
bool gn_verilog_ams_flag = false;


/*
 * For some generations we allow a system function to be called
 * as a task and only print a warning message. The default for
 * this is that it is a run time error.
 */
ivl_sfunc_as_task_t def_sfunc_as_task = IVL_SFUNC_AS_TASK_ERROR;

map<string,const char*> flags;
char*vpi_module_list = 0;


map<perm_string,unsigned> missing_modules;
map<perm_string,bool> library_file_map;

vector<perm_string> source_files;

list<const char*> library_suff;

list<perm_string> roots;

char*ivlpp_string = 0;

char depfile_mode = 'a';
char* depfile_name = NULL;
FILE *depend_file = NULL;

/*
 * These are the warning enable flags.
 */
bool warn_implicit  = false;
bool warn_implicit_dimensions = false;
bool warn_timescale = false;
bool warn_portbinding = false;
bool warn_inf_loop = false;
bool warn_ob_select = false;
bool warn_sens_entire_vec = false;
bool warn_sens_entire_arr = false;
bool warn_anachronisms = false;
bool warn_floating_nets = false;

/*
 * Ignore errors about missing modules
 */
bool ignore_missing_modules = false;

/*
 * Debug message class flags.
 */
bool debug_scopes = false;
bool debug_eval_tree = false;
bool debug_elaborate = false;
bool debug_emit = false;
bool debug_synth2 = false;
bool debug_optimizer = false;

//bool debug_scopes = true;
//bool debug_eval_tree = true;
//bool debug_elaborate = true;
//bool debug_emit = true;
//bool debug_synth2 = true;
//bool debug_optimizer = true;
/*
 * Compilation control flags.
 */
bool separate_compilation = false;

/*
 * Optimization control flags.
 */
unsigned opt_const_func = 0;

/*
 * Miscellaneous flags.
 */
bool disable_virtual_pins = false;
unsigned long array_size_limit = 16777216;  // Minimum required by IEEE-1364?
unsigned recursive_mod_limit = 10;
bool disable_concatz_generation = false;

/*
 * Verbose messages enabled.
 */
bool verbose_flag = false;

unsigned integer_width = 32;

/*
 * Width limit for unsized expressions.
 */
unsigned width_cap = 65536;

int def_ts_units = 0;
int def_ts_prec = 0;

/*
 * Keep a heap of identifier strings that I encounter. This is a more
 * efficient way to allocate those strings.
 */
StringHeapLex lex_strings;

StringHeapLex filename_strings;

StringHeapLex bits_strings;

const bool CASE_SENSITIVE = false;



bool synthesis = true;

extern MyDesign* My_elaborate(list <perm_string> root);
extern int My_show_netlist(MyDesign* des);

static void find_module_mention(map<perm_string, bool>& check_map, Module* m);
static void find_module_mention(map<perm_string, bool>& check_map, PGenerate* s);

void remove_brackets(std::string& line) {
	line.erase(std::remove(line.begin(), line.end(), '('), line.end());
	line.erase(std::remove(line.begin(), line.end(), ')'), line.end());
}

int main(int argc, char*argv[])
{
	vector<vector<int>> map_node;
	vector<char> map_name;
	BlifToV(map_node,map_name);
	const std::string inputFileName = "op_exp0_bracket.v";
	const std::string tempFileName = "temp_op_exp0_bracket.v";

	std::ifstream inputFile(inputFileName);
	std::ofstream tempFile(tempFileName);

	if (!inputFile.is_open()) {
		std::cerr << "Failed to open input file!\n";
		return 1;
	}

	if (!tempFile.is_open()) {
		std::cerr << "Failed to create temporary file!\n";
		return 1;
	}

	std::string line;
	int lineCount = 0;
	while (std::getline(inputFile, line)) {
		++lineCount;
		if (lineCount > 1) {  // 跳过第一行
			bool hasOuterOperator = false;
			bool hasInnerOperator = false;
			for (char c : line) {
				if (c == '+' || c == '-' || c == '*' || c == '/') {
					if (c == '*' || c == '/') {
						hasOuterOperator = true;
					}
					else {
						hasInnerOperator = true;
					}
				}
			}
			if (hasOuterOperator && hasInnerOperator) {
				tempFile << line << '\n';  // 保留括号
			}
			else {
				remove_brackets(line);  // 删除每一行的括号
				tempFile << line << '\n';
			}
		}
		else {
			tempFile << line << '\n';  // 写入第一行
		}
	}

	inputFile.close();
	tempFile.close();

	// 将临时文件内容复制回原文件
	std::ifstream tempInput(tempFileName);
	std::ofstream outputFile(inputFileName, std::ofstream::trunc);  // 清空原文件内容

	if (!tempInput.is_open()) {
		std::cerr << "Failed to reopen temporary file!\n";
		return 1;
	}

	if (!outputFile.is_open()) {
		std::cerr << "Failed to open output file!\n";
		return 1;
	}

	while (std::getline(tempInput, line)) {
		outputFile << line << '\n';  // 将临时文件的内容写回原文件
	}

	tempInput.close();
	outputFile.close();

	// 删除临时文件
	std::remove(tempFileName.c_str());


	const char* net_path = "netlist_dump.txt";
	const char* pf_path = "pform_dump.txt";


	flags["-o"] = strdup("a.out");


	int arg = 2;
	while (arg < argc) {
		perm_string path = filename_strings.make(argv[arg++]);
		source_files.push_back(path);
	}

	if (source_files.empty()) {
		cerr << "No input files." << endl;
		return 1;
	}

	
	lexor_keyword_mask = 0;
	switch (generation_flag) {
	case GN_VER2012:
		lexor_keyword_mask |= GN_KEYWORDS_1800_2012;
		// fallthrough
	case GN_VER2009:
		lexor_keyword_mask |= GN_KEYWORDS_1800_2009;
		// fallthrough
	case GN_VER2005_SV:
		lexor_keyword_mask |= GN_KEYWORDS_1800_2005;
		// fallthrough
	case GN_VER2005:
		lexor_keyword_mask |= GN_KEYWORDS_1364_2005;
		// fallthrough
	case GN_VER2001:
		lexor_keyword_mask |= GN_KEYWORDS_1364_2001_CONFIG;
		// fallthrough
	case GN_VER2001_NOCONFIG:
		lexor_keyword_mask |= GN_KEYWORDS_1364_2001;
		// fallthrough
	case GN_VER1995:
		lexor_keyword_mask |= GN_KEYWORDS_1364_1995;
	}

	/* Parse the input. Make the pform. */
	cout << "INPUT PARSE............to be implemented" << endl;

	int rc = 0;
	for (unsigned idx = 0; idx < source_files.size(); idx += 1) {
		rc += pform_parse(source_files[idx]);
	}

	if (rc) {
		return rc;
	}

	if (roots.empty()) {
		map<perm_string, bool> mentioned_p;
		map<perm_string, Module*>::iterator mod;
		if (verbose_flag)
			cout << "LOCATING TOP-LEVEL MODULES" << endl << "  ";
		for (mod = pform_modules.begin()
			; mod != pform_modules.end(); ++mod) {
			find_module_mention(mentioned_p, mod->second);
		}

		for (mod = pform_modules.begin()
			; mod != pform_modules.end(); ++mod) {

			if (!(*mod).second->can_be_toplevel())
				continue;

			/* Don't choose modules instantiated in other
			   modules. */
			if (mentioned_p[(*mod).second->mod_name()])
				continue;

			/* What's left might as well be chosen as a root. */
			if (verbose_flag)
				cout << " " << (*mod).second->mod_name();
			roots.push_back((*mod).second->mod_name());
		}
		if (verbose_flag)
			cout << endl;
	}

	cout << "ELABORATING DESIGN.....to be implemented" << endl;
	
	MyDesign* des = My_elaborate(roots);

	cout << "SHOW NETLIST...........to be implemented" << endl;
	My_show_netlist(des);


	delete des;

	/* Done with all the pform data. Delete the modules. */
	for (map<perm_string, Module*>::iterator idx = pform_modules.begin()
		; idx != pform_modules.end(); ++idx) {

		delete (*idx).second;
		(*idx).second = 0;
	}

	return 0;

errors_summary:
	if (!missing_modules.empty()) {
		cerr << "*** These modules were missing:" << endl;

		map<perm_string, unsigned>::const_iterator idx;
		for (idx = missing_modules.begin()
			; idx != missing_modules.end(); ++idx)
			cerr << "        " << (*idx).first
			<< " referenced " << (*idx).second
			<< " times." << endl;

		cerr << "***" << endl;
	}

	int rtn = 0; 
	return rtn;
}

void pre_process_failed(const char*text)
{
      const char*num_start = strchr(text, '(') + 1;
      unsigned long res;
      char*rem;
      res = strtoul(num_start, &rem, 10);
      assert(res > 0);
      assert(rem[0] == ')');
      pre_process_fail_count += res;
}

static void find_module_mention(map<perm_string, bool>& check_map, Module* mod)
{
	list<PGate*> gates = mod->get_gates();
	list<PGate*>::const_iterator gate;
	for (gate = gates.begin(); gate != gates.end(); ++gate) {
		PGModule* tmp = dynamic_cast<PGModule*>(*gate);
		if (tmp) {
			// Note that this module has been instantiated
			check_map[tmp->get_type()] = true;
		}
	}

	list<PGenerate*>::const_iterator cur;
	for (cur = mod->generate_schemes.begin()
		; cur != mod->generate_schemes.end(); ++cur) {
		find_module_mention(check_map, *cur);
	}
}

static void find_module_mention(map<perm_string, bool>& check_map, PGenerate* schm)
{
	list<PGate*>::const_iterator gate;
	for (gate = schm->gates.begin(); gate != schm->gates.end(); ++gate) {
		PGModule* tmp = dynamic_cast<PGModule*>(*gate);
		if (tmp) {
			// Note that this module has been instantiated
			check_map[tmp->get_type()] = true;
		}
	}

	list<PGenerate*>::const_iterator cur;
	for (cur = schm->generate_schemes.begin()
		; cur != schm->generate_schemes.end(); ++cur) {
		find_module_mention(check_map, *cur);
	}
}