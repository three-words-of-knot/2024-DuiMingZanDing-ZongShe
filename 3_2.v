module op_exp0_bracket(a,b,c,d,q);
input a,b,c,d;
output q;
wire sum1,sum2;
assign sum1 = a +b+c;
assign sum2 = a +c+b;
assign q = sum1 & sum2;
endmodule