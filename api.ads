package API is 

	procedure adaPunchTicket(id : integer);
	pragma Export (CPP, adaPunchTicket, "adaPunchTicket" );
	 
	procedure adaPurchaseTicket(id : integer);
	pragma Export (CPP, adaPurchaseTicket, "adaPurchaseTicket" );
	 
	procedure Initialize_API; 
	pragma Export (CPP, Initialize_API); 

	procedure Finalize_Api; 
	pragma Export (CPP, Finalize_API); 
	
end API; 
