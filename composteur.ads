package composteur is

   task type ComposteurTask is
      entry punch;
   end ComposteurTask;

   type ComposteurTaskAccess is access ComposteurTask;

   type ComposteurObject is
      record
         tache:ComposteurTaskAccess;
      end record;

end composteur;
