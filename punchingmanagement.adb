with Text_IO;  
with punchingTerminal;
with Interfaces;

package body punchingManagement is
use Text_IO;
use Interfaces;
use punchingTerminal;

   procedure adaPunchTicket(id : in C.Int) is
   begin
      --punchingTab(Integer(id)).punch;
      null;
   end adaPunchTicket;

end punchingManagement;
