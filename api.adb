with punchingManagement;
with purchasingManagement;

package body API is 

	procedure adaPunchTicket(id : integer) is
	begin
		punchingManagement.adaPunchTicket(id);
	end adaPunchTicket;

	procedure adaPurchaseTicket(id : integer) is
	begin
		purchasingManagement.adaPurchaseTicket(id);
	end adaPurchaseTicket;

	procedure Initialize_API is 
      procedure Adainit; 
      pragma Import (CPP, Adainit); 
   begin 
      Adainit; 
   end Initialize_API; 
 
   procedure Finalize_API is 
      procedure Adafinal; 
      pragma Import (CPP, Adafinal); 
   begin 
      Adafinal; 
   end Finalize_API;
    
end API; 
