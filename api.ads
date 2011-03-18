with Text_Io; use Text_Io;
with Interfaces.C; use Interfaces; 

package API is 

procedure Flip_Flop1;
pragma Export
(Convention    => CPP,
 Entity        => Flip_Flop1,
 External_Name => "Flip_Flop1" );
procedure Initialize_API; 
procedure Finalize_Api; 
pragma Export (CPP, Initialize_API); 
pragma Export (CPP, Finalize_API); 
end API; 
