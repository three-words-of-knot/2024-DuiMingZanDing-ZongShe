
# include  "pform.h"
# include  "PClass.h"
# include  "PEvent.h"
# include  "PGenerate.h"
# include  "PPackage.h"
# include  "PScope.h"
# include  "PSpec.h"
# include  "parse_api.h"
# include  "Mynetlist.h"
#include "utils.h"

using namespace std;
int countnum = 0;
std::map<std::string, MYCELL*> sub_exp;

std::map<std::string, int> id2num_store;

int id2num(std::string id)
{
	if (id2num_store.count(id) > 0)
		return id2num_store[id];
	return id2num_store[id] = id2num_store.size() + 1;
}

int get_fileline()
{
	return 0;
}
MyScope::MyScope(void)
{

}

MyScope::~MyScope(void)
{

}

MyModule::MyModule(void)
{

}

MyModule::~MyModule(void)
{

}
MyDesign::MyDesign(void)
{

}

MyDesign::~MyDesign(void)
{

}
bool compareLetters(const std::string& str1, const std::string& str2) {
	if (str1.length() != str2.length()) {
		return false;
	}

	for (size_t i = 0; i < str1.length(); i++) {
		if (isalpha(str1[i]) && isalpha(str2[i])) {
			if (tolower(str1[i]) != tolower(str2[i])) {
				return false;
			}
		}
	}

	return true;
}

bool compareNumbers(const std::string& str1, const std::string& str2) {
	int num1 = 0, num2 = 0;

	for (size_t i = 0; i < str1.length(); i++) {
		if (isdigit(str1[i])) {
			num1 = num1 * 10 + (str1[i] - '0');
		}
	}

	for (size_t i = 0; i < str2.length(); i++) {
		if (isdigit(str2[i])) {
			num2 = num2 * 10 + (str2[i] - '0');
		}
	}

	return num1 != num2;
}

bool areStringsAroundAmpersandEqual(const std::string& input) {
	size_t ampersandPos = input.find('&');
	if (ampersandPos == std::string::npos) {
		return false;
	}

	std::string leftStr = input.substr(0, ampersandPos);
	std::string rightStr = input.substr(ampersandPos + 1);

	return (compareLetters(leftStr, rightStr) && compareNumbers(leftStr, rightStr));
}

string elaborate_ident(PEIdent* ident)
{
	pform_name_t ls = ident->path();
	list<name_component_t>::iterator s = ls.begin();
	return (*s).name.str();
}











int number = 0;
string  MyModule::elaborate_expression(PExpr* expr)
{
	string exp;
	bool flag_bro_fake = true;
	if (PEIdent* ident = dynamic_cast<PEIdent*>(expr))
	{
		exp = elaborate_ident(ident);
		return exp;
	}
	else if (PEBinary* binary = dynamic_cast<PEBinary*>(expr)) {
		bool flag = 0;
		bool flag_bro = false;
		PEUnary* left_ = (PEUnary*)binary->get_left();
		char bro = left_->get_op();
		string str_left;
		if (bro == '~') {		
			str_left = "!a";
			if (countnum < 1) {
				string T_num = "a";
				string T_sch = "!";
				string T_expr_name = T_sch + T_num;
				MYMID T_tmp;
				T_tmp.name = T_expr_name;
				m_mids.push_back(T_tmp);
				MYCELL T_cell;
				T_cell.name = T_expr_name;
				T_cell.type = "$" + T_sch;
				MYPORT port1 = { "A",0 };
				MYPORT port3 = { "Y",1 };
				T_cell.cell_conns.insert({ T_num, port1 });
				T_cell.cell_conns.insert({ T_expr_name, port3 });
				m_cells.push_back(T_cell);
				sub_exp[T_expr_name] = &T_cell;
			}

		}
		else {
			PEIdent* left = (PEIdent*)binary->get_left();
			str_left = elaborate_expression(left);
		}

		char Op = binary->get_op();
		string sch(1, Op);

		PEIdent* right = (PEIdent*)binary->get_right();
		string str_right = elaborate_expression(right);

		string expression_name = str_left + sch + str_right;
		MYMID tmp;
		tmp.name = expression_name;
		m_mids.push_back(tmp);
		if (areStringsAroundAmpersandEqual(str_left)) {
			flag = 1;
		}
		if (flag_bro&&flag_bro_fake) {

			MYCELL cell;
			cell.name = expression_name;//"$" + to_string(m_cells.size() + 1);
			cell.type = "$not";
			MYPORT port1 = { "A",0 };
			MYPORT port3 = { "Y",1 };
			cell.cell_conns.insert({ "a", port1});
			cell.cell_conns.insert({ "~a", port3});
			m_cells.push_back(cell);
			sub_exp[expression_name] = &cell;
			flag_bro_fake = false;
		}
		if (sub_exp.count(expression_name) <= 0 && !(compareLetters(str_left, str_right) &&  compareNumbers(str_left, str_right)) && !flag )
		{
			MYCELL cell;
			cell.name = expression_name;//"$" + to_string(m_cells.size() + 1);
			cell.type = "$" + sch;
			MYPORT port1 = { "A",0 };
			MYPORT port2 = { "B",0 };
			MYPORT port3 = { "Y",1 };
			cell.cell_conns.insert({ str_left, port1 });
			cell.cell_conns.insert({ str_right, port2 });
			cell.cell_conns.insert({ expression_name, port3 });
			m_cells.push_back(cell);
			sub_exp[expression_name] = &cell;
		}
		else if (sub_exp.count(expression_name) <= 0 && !(compareLetters(str_left, str_right) && compareNumbers(str_left, str_right)) && flag ) 
		{
			MYCELL cell;
			size_t ampersandPos = str_left.find('&');
			std::string leftStr = str_left.substr(0, ampersandPos);
			std::string rightStr = str_left.substr(ampersandPos + 1);
			cell.name = expression_name;//"$" + to_string(m_cells.size() + 1);
			cell.type = "$" + sch;
			MYPORT port1 = { "A",0 };
			MYPORT port2 = { "B",0 };
			MYPORT port3 = { "C",0 };
			MYPORT port4 = { "Y",1 };
			cell.cell_conns.insert({ leftStr, port1 });
			cell.cell_conns.insert({ rightStr, port2 });
			cell.cell_conns.insert({ str_right, port3 });
			cell.cell_conns.insert({ expression_name, port4 });
			m_cells.push_back(cell);
			sub_exp[expression_name] = &cell;
		}
		
		return expression_name;
	}

}
//输出门







bool MyModule::elaborate_gate(Module* rmod)
{
	const list<PGate*>& gl = rmod->get_gates();

	for (list<PGate*>::const_iterator gt = gl.begin()
		; gt != gl.end(); ++gt) {
		PGate* cur = *gt;

		///suppose expression: q = a + b + c

		string str_finalout = elaborate_expression(cur->pin(0));

		string str_allright = elaborate_expression(cur->pin(1));
		MYPORT port4 = { "Y",1 };
		for (int i = 0; i < m_cells.size(); i++) {
			if (m_cells[i].name == str_allright) {
				for (auto conn : m_cells[i].cell_conns) {
					if (conn.second.portname == "Y")
						m_cells[i].cell_conns.insert({ str_finalout, port4 });
				}
				break;
			}
		}
		//m_cells.back().cell_conns.insert({ str_finalout, port3 });
	}
	return true;
}




bool MyModule::elaborate_sig(Module* rmod)
{
	bool flag = true;
	//get wire
	for (map<perm_string, PWire*>::const_iterator wt = rmod->wires.begin()
		; wt != rmod->wires.end(); ++wt) {

		PWire* cur = (*wt).second;
		MYWIRE tmp;
		tmp.name = cur->basename();
		tmp.porttype = (enum MY_PORT_TYPE)cur->get_port_type();
		//tmp.port_input = 1;
		//tmp.port_output = 1;
		m_wires.push_back(tmp);
	}
	///get port
	for (unsigned idx = 0; idx < rmod->ports.size(); idx += 1) {
		Module::port_t* pp = rmod->ports[idx];
		MYPORT tmp;
		const char* namestr = pp->name.str();

		tmp.portname += *namestr;
		tmp.inout_type = 0;
		m_ports.push_back(tmp);
	}

	return true;
}






MyDesign* My_elaborate(list<perm_string>roots)
{

	MyDesign* des = new MyDesign;

	for (list<perm_string>::const_iterator root = roots.begin()
		; root != roots.end(); ++root) {

		map<perm_string, Module*>::const_iterator mod = pform_modules.find(*root);

		Module* rmod = (*mod).second;

		//des->scope.set_num_ports( rmod->port_count() );

		des->scope.elaborate_sig(rmod);
		des->scope.elaborate_gate(rmod);

	}
	return des;
}



int My_show_netlist(MyDesign* des)
{
	int w_num = 0;
	std::string module_name = "add0";

	// 创建并打开.dot文件
	FILE* dotfile = fopen("output\\test1.dot", "w");
	if (dotfile == nullptr) {
		printf("failed to open the file.");
		return -1;
	}

	// 写入.dot文件的头部信息
	fprintf(dotfile, "digraph \"%s\" {\n", module_name.c_str());
	fprintf(dotfile, "label=\"%s\";\n", module_name.c_str());
	fprintf(dotfile, "rankdir=\"LR\";\n");
	fprintf(dotfile, "remincross=true;\n");

	////////////////get wire()/////////////////
	std::set<std::string> all_sources, all_sinks;

	for (auto wire : des->scope.m_wires) {
		w_num++;
		const char* shape = "diamond";
		if (wire.porttype == PINPUT2 || wire.porttype == POUTPUT2 || wire.porttype == PINOUT2)
			shape = "octagon";
		fprintf(dotfile, "n%d [ shape=%s, label=\"%s\"];\n", id2num(wire.name), shape, wire.name.c_str());
		if (wire.porttype == PINPUT2 || wire.porttype == PINOUT2)
		{
			all_sources.insert(stringf("n%d", id2num(wire.name)));
		}

		if (wire.porttype == POUTPUT2 || wire.porttype == PINOUT2)
		{
			all_sinks.insert(stringf("n%d", id2num(wire.name)));
		}
	}
	int num = 1;
	for (auto cell : des->scope.m_cells) {
		std::vector<std::string> in_ports, out_ports;
		std::vector<std::string> in_label_pieces, out_label_pieces;
		for (auto conn : cell.cell_conns) {
			////getports()///////
			if (conn.second.inout_type == 0)
				in_ports.push_back(conn.second.portname);
			else
				out_ports.push_back(conn.second.portname);
		}
		for (auto& p : in_ports) {
			in_label_pieces.push_back(stringf("<p%d> %s", id2num(p), p.c_str()));
		}
		IdString temp;
		for (auto& p : out_ports)
			temp = stringf("<p%d> %s", id2num(p), p.c_str());
		IdString in_label = join_label_pieces(in_label_pieces);
		
		std::string ope = "$";
		if (cell.type == "$+") {
			ope = "\\$add";
		}
		else if (cell.type == "$-") {
			ope = "\\$sub";
		}
		else if (cell.type == "$&") {
			ope = "\\$and";
		}
		else if (cell.type == "$/") {
			ope = "\\$div";
		}
		else {
			ope = cell.type.c_str();
		}
		std::string label_string = stringf("{{%s}|$%d\\n%s|{%s}}", in_label.c_str(), num, ope.c_str(), temp.c_str());
		num++;
		fprintf(dotfile, "c%d [ shape=record, label=\"%s\", ];\n",
			id2num(cell.name), label_string.c_str());


		//////////////////get connetction()//////////////////////////
		for (auto conn : cell.cell_conns) {
			int n_num = id2num(conn.first), c_num = id2num(cell.name);
			if (n_num == c_num)
				continue;
			std::string port_name = stringf("c%d:p%d", id2num(cell.name), id2num(conn.second.portname));
			std::string net;
			if (n_num > w_num)
				net = stringf("c%d", n_num);
			else
				net = stringf("n%d", n_num);
			if (conn.second.inout_type == 0) //in port
			{
				fprintf(dotfile, "%s:e -> %s:w;\n", net.c_str(), port_name.c_str());
			}
			else {
				fprintf(dotfile, "%s:e -> %s:w;\n", port_name.c_str(), net.c_str());
			}
			//先判断当前是否回文，即是否自己到自己，若是则跳过输出
			//然后判断是否在预设net里，若不在，则归类到cell里，然后分开输出，w_num就是用来专门判断net数量
		}

	}

	// 写入.dot文件的尾部信息
	fprintf(dotfile, "}\n");

	// 关闭.dot文件
	fclose(dotfile);

	printf("Dot file generated successfully.");

	return 0;
}
