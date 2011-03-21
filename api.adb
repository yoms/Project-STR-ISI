with Interfaces;

package body API is 

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
