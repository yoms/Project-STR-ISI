with punchingTerminal; use punchingTerminal;
with Ada.Containers.Ordered_Maps;
with Interfaces.C;

package punchingManagement is

   package PunchingMapType is new Ada.Containers.Ordered_Maps(integer, PunchingRecord);
   punchingMap : PunchingMapType.Map;
   
   procedure createPunchingTerminal(id: in integer);
   pragma Export (C, createPunchingTerminal, "createPunchingTerminal");

   procedure punchTicket(id: in integer);
   pragma Export (C, punchTicket, "punchTicket");

end punchingManagement;
