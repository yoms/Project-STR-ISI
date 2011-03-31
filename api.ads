with Text_Io; use Text_Io;
with Interfaces.C; use Interfaces; 

package API is 

procedure adaPunchTicket(id : integer);
pragma Export
(Convention    => CPP,
 Entity        => adaPunchTicket,
 External_Name => "adaPunchTicket" );
procedure Initialize_API; 
procedure Finalize_Api; 
pragma Export (CPP, Initialize_API); 
pragma Export (CPP, Finalize_API); 
end API; 
