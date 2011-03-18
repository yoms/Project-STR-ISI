with Text_Io; use Text_Io;
with Interfaces;
with Ada.Exceptions;

package body API is 

procedure Flip_Flop1 is
use Ada.Exceptions;

   task Flip is
      entry Vas_Y;
   end Flip;

   task Flop is
      entry Vas_Y;
   end Flop;

   task body Flip is
   begin
      for K in 1..10 loop
         accept Vas_Y;
         Put_Line("FLIP");
         Flop.Vas_Y;
      end loop;
   exception
      when E :others =>
         Put_Line("Probleme dans Flip: ");
         Put_Line(Exception_Name(E));
   end Flip;

   task body Flop is
   begin
      for K in 1..10 loop
         accept Vas_Y;
         Put_Line("FLOP");
         Flip.Vas_Y;
      end loop;
   exception
      when E :others =>
         Put_Line("Probleme dans Flop: ");
         Put_Line(Exception_Name(E));
   end Flop;


begin
   Flip.Vas_Y;
end Flip_Flop1;
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
