with Text_IO;  use Text_IO;
with composteur; use composteur;

package body gestionComposteur is

   procedure createComposteur(id : in integer) is
      newComposteurObject : ComposteurObject;
   begin
      newComposteurObject.tache := new ComposteurTask;
      composteurs.insert(id, newComposteurObject);
   end createComposteur;

   procedure punchTicket(id : in integer) is
   begin
      composteurs.element(id).tache.all.punch;
   end punchTicket;

end gestionComposteur;
