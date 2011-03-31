package purchasingManagement is

   task type PurchasingTask is
      entry purchase;
   end PurchasingTask;

   purchaseTab : array(1..10) of PurchasingTask;

   procedure adaPurchaseTicket(id : integer);

end purchasingManagement;
