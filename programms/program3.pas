program test;

var
	sum, t: integer;
begin
	sum := 0;
	
	read(t);
	
	while (t <> 0) do begin
		sum := sum + t;
		read(t);
	end;
	
	write(sum);
end.