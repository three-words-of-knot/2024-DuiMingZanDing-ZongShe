/* A Bison parser, made by GNU Bison 3.5.1.  */

/* Bison interface for Yacc-like parsers in C

   Copyright (C) 1984, 1989-1990, 2000-2015, 2018-2020 Free Software Foundation,
   Inc.

   This program is free software: you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation, either version 3 of the License, or
   (at your option) any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program.  If not, see <http://www.gnu.org/licenses/>.  */

/* As a special exception, you may create a larger work that contains
   part or all of the Bison parser skeleton and distribute that work
   under terms of your choice, so long as that work isn't itself a
   parser generator using the skeleton or a modified version thereof
   as a parser skeleton.  Alternatively, if you modify or redistribute
   the parser skeleton itself, you may (at your option) remove this
   special exception, which will cause the skeleton and the resulting
   Bison output files to be licensed under the GNU General Public
   License without this special exception.

   This special exception was added by the Free Software Foundation in
   version 2.2 of Bison.  */

/* Undocumented macros, especially those whose name start with YY_,
   are private implementation details.  Do not rely on them.  */

#ifndef YY_VL_PARSE_H_INCLUDED
# define YY_VL_PARSE_H_INCLUDED
/* Debug traces.  */
#ifndef YYDEBUG
# define YYDEBUG 1
#endif
#if YYDEBUG
extern int VLdebug;
#endif

/* Token type.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
  enum yytokentype
  {
    IDENTIFIER = 258,
    SYSTEM_IDENTIFIER = 259,
    STRING = 260,
    TIME_LITERAL = 261,
    TYPE_IDENTIFIER = 262,
    PACKAGE_IDENTIFIER = 263,
    DISCIPLINE_IDENTIFIER = 264,
    PATHPULSE_IDENTIFIER = 265,
    BASED_NUMBER = 266,
    DEC_NUMBER = 267,
    UNBASED_NUMBER = 268,
    REALTIME = 269,
    K_PLUS_EQ = 270,
    K_MINUS_EQ = 271,
    K_INCR = 272,
    K_DECR = 273,
    K_LE = 274,
    K_GE = 275,
    K_EG = 276,
    K_EQ = 277,
    K_NE = 278,
    K_CEQ = 279,
    K_CNE = 280,
    K_WEQ = 281,
    K_WNE = 282,
    K_LP = 283,
    K_LS = 284,
    K_RS = 285,
    K_RSS = 286,
    K_SG = 287,
    K_CONTRIBUTE = 288,
    K_PO_POS = 289,
    K_PO_NEG = 290,
    K_POW = 291,
    K_PSTAR = 292,
    K_STARP = 293,
    K_DOTSTAR = 294,
    K_LOR = 295,
    K_LAND = 296,
    K_NAND = 297,
    K_NOR = 298,
    K_NXOR = 299,
    K_TRIGGER = 300,
    K_NB_TRIGGER = 301,
    K_LEQUIV = 302,
    K_SCOPE_RES = 303,
    K_edge_descriptor = 304,
    K_CONSTRAINT_IMPL = 305,
    K_always = 306,
    K_and = 307,
    K_assign = 308,
    K_begin = 309,
    K_buf = 310,
    K_bufif0 = 311,
    K_bufif1 = 312,
    K_case = 313,
    K_casex = 314,
    K_casez = 315,
    K_cmos = 316,
    K_deassign = 317,
    K_default = 318,
    K_defparam = 319,
    K_disable = 320,
    K_edge = 321,
    K_else = 322,
    K_end = 323,
    K_endcase = 324,
    K_endfunction = 325,
    K_endmodule = 326,
    K_endprimitive = 327,
    K_endspecify = 328,
    K_endtable = 329,
    K_endtask = 330,
    K_event = 331,
    K_for = 332,
    K_force = 333,
    K_forever = 334,
    K_fork = 335,
    K_function = 336,
    K_highz0 = 337,
    K_highz1 = 338,
    K_if = 339,
    K_ifnone = 340,
    K_initial = 341,
    K_inout = 342,
    K_input = 343,
    K_integer = 344,
    K_join = 345,
    K_large = 346,
    K_macromodule = 347,
    K_medium = 348,
    K_module = 349,
    K_nand = 350,
    K_negedge = 351,
    K_nmos = 352,
    K_nor = 353,
    K_not = 354,
    K_notif0 = 355,
    K_notif1 = 356,
    K_or = 357,
    K_output = 358,
    K_parameter = 359,
    K_pmos = 360,
    K_posedge = 361,
    K_primitive = 362,
    K_pull0 = 363,
    K_pull1 = 364,
    K_pulldown = 365,
    K_pullup = 366,
    K_rcmos = 367,
    K_real = 368,
    K_realtime = 369,
    K_reg = 370,
    K_release = 371,
    K_repeat = 372,
    K_rnmos = 373,
    K_rpmos = 374,
    K_rtran = 375,
    K_rtranif0 = 376,
    K_rtranif1 = 377,
    K_scalared = 378,
    K_small = 379,
    K_specify = 380,
    K_specparam = 381,
    K_strong0 = 382,
    K_strong1 = 383,
    K_supply0 = 384,
    K_supply1 = 385,
    K_table = 386,
    K_task = 387,
    K_time = 388,
    K_tran = 389,
    K_tranif0 = 390,
    K_tranif1 = 391,
    K_tri = 392,
    K_tri0 = 393,
    K_tri1 = 394,
    K_triand = 395,
    K_trior = 396,
    K_trireg = 397,
    K_vectored = 398,
    K_wait = 399,
    K_wand = 400,
    K_weak0 = 401,
    K_weak1 = 402,
    K_while = 403,
    K_wire = 404,
    K_wor = 405,
    K_xnor = 406,
    K_xor = 407,
    K_Shold = 408,
    K_Snochange = 409,
    K_Speriod = 410,
    K_Srecovery = 411,
    K_Ssetup = 412,
    K_Ssetuphold = 413,
    K_Sskew = 414,
    K_Swidth = 415,
    KK_attribute = 416,
    K_bool = 417,
    K_logic = 418,
    K_automatic = 419,
    K_endgenerate = 420,
    K_generate = 421,
    K_genvar = 422,
    K_localparam = 423,
    K_noshowcancelled = 424,
    K_pulsestyle_onevent = 425,
    K_pulsestyle_ondetect = 426,
    K_showcancelled = 427,
    K_signed = 428,
    K_unsigned = 429,
    K_Sfullskew = 430,
    K_Srecrem = 431,
    K_Sremoval = 432,
    K_Stimeskew = 433,
    K_cell = 434,
    K_config = 435,
    K_design = 436,
    K_endconfig = 437,
    K_incdir = 438,
    K_include = 439,
    K_instance = 440,
    K_liblist = 441,
    K_library = 442,
    K_use = 443,
    K_wone = 444,
    K_uwire = 445,
    K_alias = 446,
    K_always_comb = 447,
    K_always_ff = 448,
    K_always_latch = 449,
    K_assert = 450,
    K_assume = 451,
    K_before = 452,
    K_bind = 453,
    K_bins = 454,
    K_binsof = 455,
    K_bit = 456,
    K_break = 457,
    K_byte = 458,
    K_chandle = 459,
    K_class = 460,
    K_clocking = 461,
    K_const = 462,
    K_constraint = 463,
    K_context = 464,
    K_continue = 465,
    K_cover = 466,
    K_covergroup = 467,
    K_coverpoint = 468,
    K_cross = 469,
    K_dist = 470,
    K_do = 471,
    K_endclass = 472,
    K_endclocking = 473,
    K_endgroup = 474,
    K_endinterface = 475,
    K_endpackage = 476,
    K_endprogram = 477,
    K_endproperty = 478,
    K_endsequence = 479,
    K_enum = 480,
    K_expect = 481,
    K_export = 482,
    K_extends = 483,
    K_extern = 484,
    K_final = 485,
    K_first_match = 486,
    K_foreach = 487,
    K_forkjoin = 488,
    K_iff = 489,
    K_ignore_bins = 490,
    K_illegal_bins = 491,
    K_import = 492,
    K_inside = 493,
    K_int = 494,
    K_interface = 495,
    K_intersect = 496,
    K_join_any = 497,
    K_join_none = 498,
    K_local = 499,
    K_longint = 500,
    K_matches = 501,
    K_modport = 502,
    K_new = 503,
    K_null = 504,
    K_package = 505,
    K_packed = 506,
    K_priority = 507,
    K_program = 508,
    K_property = 509,
    K_protected = 510,
    K_pure = 511,
    K_rand = 512,
    K_randc = 513,
    K_randcase = 514,
    K_randsequence = 515,
    K_ref = 516,
    K_return = 517,
    K_sequence = 518,
    K_shortint = 519,
    K_shortreal = 520,
    K_solve = 521,
    K_static = 522,
    K_string = 523,
    K_struct = 524,
    K_super = 525,
    K_tagged = 526,
    K_this = 527,
    K_throughout = 528,
    K_timeprecision = 529,
    K_timeunit = 530,
    K_type = 531,
    K_typedef = 532,
    K_union = 533,
    K_unique = 534,
    K_var = 535,
    K_virtual = 536,
    K_void = 537,
    K_wait_order = 538,
    K_wildcard = 539,
    K_with = 540,
    K_within = 541,
    K_accept_on = 542,
    K_checker = 543,
    K_endchecker = 544,
    K_eventually = 545,
    K_global = 546,
    K_implies = 547,
    K_let = 548,
    K_nexttime = 549,
    K_reject_on = 550,
    K_restrict = 551,
    K_s_always = 552,
    K_s_eventually = 553,
    K_s_nexttime = 554,
    K_s_until = 555,
    K_s_until_with = 556,
    K_strong = 557,
    K_sync_accept_on = 558,
    K_sync_reject_on = 559,
    K_unique0 = 560,
    K_until = 561,
    K_until_with = 562,
    K_untyped = 563,
    K_weak = 564,
    K_implements = 565,
    K_interconnect = 566,
    K_nettype = 567,
    K_soft = 568,
    K_above = 569,
    K_abs = 570,
    K_absdelay = 571,
    K_abstol = 572,
    K_access = 573,
    K_acos = 574,
    K_acosh = 575,
    K_ac_stim = 576,
    K_aliasparam = 577,
    K_analog = 578,
    K_analysis = 579,
    K_asin = 580,
    K_asinh = 581,
    K_atan = 582,
    K_atan2 = 583,
    K_atanh = 584,
    K_branch = 585,
    K_ceil = 586,
    K_connect = 587,
    K_connectmodule = 588,
    K_connectrules = 589,
    K_continuous = 590,
    K_cos = 591,
    K_cosh = 592,
    K_ddt = 593,
    K_ddt_nature = 594,
    K_ddx = 595,
    K_discipline = 596,
    K_discrete = 597,
    K_domain = 598,
    K_driver_update = 599,
    K_endconnectrules = 600,
    K_enddiscipline = 601,
    K_endnature = 602,
    K_endparamset = 603,
    K_exclude = 604,
    K_exp = 605,
    K_final_step = 606,
    K_flicker_noise = 607,
    K_floor = 608,
    K_flow = 609,
    K_from = 610,
    K_ground = 611,
    K_hypot = 612,
    K_idt = 613,
    K_idtmod = 614,
    K_idt_nature = 615,
    K_inf = 616,
    K_initial_step = 617,
    K_laplace_nd = 618,
    K_laplace_np = 619,
    K_laplace_zd = 620,
    K_laplace_zp = 621,
    K_last_crossing = 622,
    K_limexp = 623,
    K_ln = 624,
    K_log = 625,
    K_max = 626,
    K_merged = 627,
    K_min = 628,
    K_nature = 629,
    K_net_resolution = 630,
    K_noise_table = 631,
    K_paramset = 632,
    K_potential = 633,
    K_pow = 634,
    K_resolveto = 635,
    K_sin = 636,
    K_sinh = 637,
    K_slew = 638,
    K_split = 639,
    K_sqrt = 640,
    K_tan = 641,
    K_tanh = 642,
    K_timer = 643,
    K_transition = 644,
    K_units = 645,
    K_white_noise = 646,
    K_wreal = 647,
    K_zi_nd = 648,
    K_zi_np = 649,
    K_zi_zd = 650,
    K_zi_zp = 651,
    K_TAND = 652,
    K_MUL_EQ = 653,
    K_DIV_EQ = 654,
    K_MOD_EQ = 655,
    K_AND_EQ = 656,
    K_OR_EQ = 657,
    K_XOR_EQ = 658,
    K_LS_EQ = 659,
    K_RS_EQ = 660,
    K_RSS_EQ = 661,
    UNARY_PREC = 662,
    less_than_K_else = 663,
    no_timeunits_declaration = 664,
    one_timeunits_declaration = 665
  };
#endif

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
union YYSTYPE
{
#line 359 "parse.y"

      bool flag;

      char letter;
      int  int_val;

      enum atom_type_t::type_code atom_type;

	/* text items are C strings allocated by the lexor using
	   strdup. They can be put into lists with the texts type. */
      char*text;
      std::list<perm_string>*perm_strings;

      std::list<pform_port_t>*port_list;

      std::vector<pform_tf_port_t>* tf_ports;

      pform_name_t*pform_name;

      ivl_discipline_t discipline;

      hname_t*hier;

      std::list<std::string>*strings;

      struct str_pair_t drive;

      PCase::Item*citem;
      std::vector<PCase::Item*>*citems;

      lgate*gate;
      std::vector<lgate>*gates;

      Module::port_t *mport;
      LexicalScope::range_t* value_range;
      std::vector<Module::port_t*>*mports;

      std::list<PLet::let_port_t*>*let_port_lst;
      PLet::let_port_t*let_port_itm;

      named_number_t* named_number;
      std::list<named_number_t>* named_numbers;

      named_pexpr_t*named_pexpr;
      std::list<named_pexpr_t>*named_pexprs;
      struct parmvalue_t*parmvalue;
      std::list<pform_range_t>*ranges;

      PExpr*expr;
      std::list<PExpr*>*exprs;

      PEEvent*event_expr;
      std::vector<PEEvent*>*event_exprs;

      ivl_case_quality_t case_quality;
      NetNet::Type nettype;
      PGBuiltin::Type gatetype;
      NetNet::PortType porttype;
      ivl_variable_type_t vartype;
      PBlock::BL_TYPE join_keyword;

      PWire*wire;
      std::vector<PWire*>*wires;

      PCallTask *subroutine_call;

      PEventStatement*event_statement;
      Statement*statement;
      std::vector<Statement*>*statement_list;

      decl_assignment_t*decl_assignment;
      std::list<decl_assignment_t*>*decl_assignments;

      struct_member_t*struct_member;
      std::list<struct_member_t*>*struct_members;
      struct_type_t*struct_type;

      data_type_t*data_type;
      class_type_t*class_type;
      real_type_t::type_t real_type;
      property_qualifier_t property_qualifier;
      PPackage*package;

      struct {
	    char*text;
	    typedef_t*type;
      } type_identifier;

      struct {
	    data_type_t*type;
	    std::list<PExpr*>*exprs;
      } class_declaration_extends;

      struct {
	    char*text;
	    PExpr*expr;
      } genvar_iter;

      struct {
	    bool packed_flag;
	    bool signed_flag;
      } packed_signing;

      verinum* number;

      verireal* realtime;

      PSpecPath* specpath;
      std::list<index_component_t> *dimensions;

      LexicalScope::lifetime_t lifetime;

      enum typedef_t::basic_type typedef_basic_type;

#line 583 "parse.h"

};
typedef union YYSTYPE YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif

/* Location type.  */
#if ! defined YYLTYPE && ! defined YYLTYPE_IS_DECLARED
typedef struct YYLTYPE YYLTYPE;
struct YYLTYPE
{
  int first_line;
  int first_column;
  int last_line;
  int last_column;
};
# define YYLTYPE_IS_DECLARED 1
# define YYLTYPE_IS_TRIVIAL 1
#endif


extern YYSTYPE VLlval;
extern YYLTYPE VLlloc;
int VLparse (void);

#endif /* !YY_VL_PARSE_H_INCLUDED  */
