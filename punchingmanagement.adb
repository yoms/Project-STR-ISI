with Text_IO;  
with punchingTerminal;
with Interfaces;

package body punchingManagement is
use Text_IO;
use Interfaces;
use punchingTerminal;
   procedure createPunchingTerminal(id : in C.Int) is
   begin
	null;
   end createPunchingTerminal;

   procedure adaPunchTicket(id : in C.Int) is
   begin
      null;--punchingTab(Integer(id)).punch;
   end adaPunchTicket;

end punchingManagement;
