with Interfaces.C; use Interfaces; 

package BorneAchat is 
	function giveTicket return boolean;
	pragma Export
	(Convention    => CPP,
	 Entity        => giveTicket,
	 External_Name => "adaGiveTicket");
end BorneAchat; 
