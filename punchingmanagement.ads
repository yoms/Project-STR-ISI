with punchingTerminal; use punchingTerminal;
with Ada.Containers.Ordered_Maps;
with Interfaces.C;

package punchingManagement is
use Interfaces;

   punchingTab : array(1..10) of PunchingTask;

   procedure adaPunchTicket(id: in C.Int);
   pragma Export (C, adaPunchTicket, "adaPunchTicket");

end punchingManagement;
