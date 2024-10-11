#ifndef MYNETLIST_H
#define MYNETLIST_H

#include <string>
#include <map>
#include <set>
#include <vector>

#include <netlist.h>
#include <Module.h>

class MyDesign;
class MyScope;
class MyModule;


using IdString = std::string;
//typedef std::string IdString;

enum MY_PORT_TYPE { NOT_A_PORT2, PIMPLICIT2, PINPUT2, POUTPUT2, PINOUT2, PREF2 };

struct MYMID
{
    IdString name;
};

struct MYWIRE
{
    IdString name;
    //bool port_input;
    //bool port_output;
    MY_PORT_TYPE porttype;
};

struct MYPORT
{
    IdString     portname;
    char        inout_type;  //0:in, 1:out
};

struct MYCELL
{
    IdString name;
    IdString type;
    std::map<IdString, MYPORT> cell_conns;  //<wirename,port>
};


class MyScope {

public:
    MyScope();
    ~MyScope();
    std::vector<MYWIRE> m_wires;
    std::vector<MYPORT> m_ports;
    std::vector<MYCELL> m_cells;
    std::vector<MYMID> m_mids;
    
    void set_num_ports(unsigned int num_ports);
private:

};

class MyModule: public MyScope {

public:
    MyModule();
    ~MyModule();
    bool elaborate_sig(Module* rmod);
    bool elaborate_gate(Module* rmod);
    string  elaborate_expression(PExpr* expr);
private:

};

class MyDesign {

public:
    MyDesign();
    ~MyDesign();

    MyModule scope;

private:

};




#endif
