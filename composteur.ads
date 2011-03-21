with Interfaces.C; use Interfaces; 

package Composteur is 
	procedure punchTicket;
	pragma Export
	(Convention    => CPP,
	 Entity        => punchTicket,
	 External_Name => "adaPunchTicket");
end Composteur; 
