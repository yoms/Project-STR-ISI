with composteur; use composteur;
with Ada.Containers.Ordered_Maps;

package gestionComposteur is

   package ComposteurMap is new Ada.Containers.Ordered_Maps(integer, ComposteurObject);
   composteurs : ComposteurMap.Map;

   procedure createComposteur(id: in integer);

   procedure punchTicket(id: in integer);

   pragma Export (CPP, punchTicket, "adaPunchTicket");
   pragma Export (CPP, createComposteur, "adaCreateComposteur");

end gestionComposteur;
