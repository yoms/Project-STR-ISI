with Text_Io; use Text_Io;
with Interfaces.C; use Interfaces; 

package API is 

Function Flip_Flop1 return integer;
pragma Export
(Convention    => C,
 Entity        => Flip_Flop1,
 External_Name => "Flip_Flop1" );
procedure Initialize_API; 
procedure Finalize_Api; 
pragma Export (C, Initialize_API); 
pragma Export (C, Finalize_API); 
end API; 
