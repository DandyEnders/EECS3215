module decimal_counter(A,OVERFLOW,CLK,RST);
input CLK, RST;
output OVERFLOW;
output [3:0] A;
reg OVERFLOW;
reg [3:0] A;
always @ (posedge CLK or negedge RST)
if (~RST) begin
	OVERFLOW <= 1'b0;
	A <= 4'b1001;
end
else if (A>0) begin
	A <= A - 1'b1;
	OVERFLOW <= 1'b0;
end
else begin
	A <= 4'b1001;
	OVERFLOW <= 1'b1;
end
endmodule
