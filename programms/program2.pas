program test;

var
	a, b: integer;
begin
	read(a, b);
	
	if (a = b) then
		write(0)
	else if (a > b) then
		write(1)
	else
		write(-1);
end.