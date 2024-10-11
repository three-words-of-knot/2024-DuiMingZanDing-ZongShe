module add0 (a,b,q);
input a,b;
output reg q;
always @(a,b)
    q = a & b ;
endmodule
