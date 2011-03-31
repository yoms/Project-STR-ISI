with Text_IO; use Text_IO;

package body purchasingManagement is

	task body PurchasingTask is
   begin
      loop
         accept purchase
         do
            delay 1.0;            
         end;
      end loop;
   end PurchasingTask;

   procedure adaPurchaseTicket(id : integer) is
   begin
      purchaseTab(id).purchase;
   end adaPurchaseTicket;

end purchasingManagement;
