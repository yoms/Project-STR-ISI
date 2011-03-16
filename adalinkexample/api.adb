with Text_Io; use Text_Io;
with Interfaces;

package body API is 

Function Flip_Flop1 return integer Is
    Task Flip Is
        Entry Vas_Y;
    End Flip;

    Task Flop Is
        Entry Vas_Y;
    End Flop;

    Task Body Flip Is
    Begin
        Loop
            Accept Vas_Y;
            Put_Line("FLIP");
            Flop.Vas_Y;
        End Loop;
    End Flip;

    Task Body Flop Is
    Begin
        Loop
            Accept Vas_Y;
            Put_Line("FLOP");
            Flip.Vas_Y;
        End Loop;
    End Flop;


Begin
    Flip.Vas_Y;
	return 0;
End Flip_Flop1;
procedure Initialize_API is 
      procedure Adainit; 
      pragma Import (C, Adainit); 
   begin 
      Adainit; 
   end Initialize_API; 
 
   procedure Finalize_API is 
      procedure Adafinal; 
      pragma Import (C, Adafinal); 
   begin 
      Adafinal; 
   end Finalize_API; 
end API; 
