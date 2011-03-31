with Text_Io; use Text_Io;
with Interfaces;
with punchingManagement;
with Ada.Exceptions;

package body API is 

procedure adaPunchTicket(id : integer) is
begin
   punchingManagement.adaPunchTicket(id);
end adaPunchTicket;

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
