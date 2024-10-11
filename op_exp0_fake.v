module op_exp0_bracket(a,b,c,d,e,q);
input a,b,c,d,e;
output q;
wire sum1,sum2,sum3;
assign sum1 = ~a + b + c;
assign sum2 = ~a +b + d;
assign sum3 = ~a +b + e;
assign q = sum1 & sum2 & sum3;
endmodule