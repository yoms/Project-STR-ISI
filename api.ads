with Interfaces.C; use Interfaces; 

package API is 

procedure Initialize_API; 
procedure Finalize_Api; 
pragma Export (CPP, Initialize_API); 
pragma Export (CPP, Finalize_API); 

end API; 
