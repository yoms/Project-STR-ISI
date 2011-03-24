with punchingTerminal; use punchingTerminal;
with Ada.Containers.Ordered_Maps;

package punchingManagement is

   package PunchingMapType is new Ada.Containers.Ordered_Maps(integer, PunchingRecord);
   punchingMap : PunchingMapType.Map;

   procedure createPunchingTerminal(id: in integer);

   procedure punchTicket(id: in integer);

   pragma Export (CPP, punchTicket, "adaPunchTicket");
   pragma Export (CPP, createPunchingTerminal, "adaCreatePunchingTerminal");

end punchingManagement;
