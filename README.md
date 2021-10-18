# weatherstation
Το έργο μας περιλαμβάνει την κατασκευή ηλεκτρονικού μετεωρολογικού σταθμού με ηλεκτρονικό βαρόμετρο, θερμόμετρο, υγρασιόμετρο και βροχόμετρο, ανεμοδείκτη, ανεμόμετρο και φωτόμετρο.
Το βροχόμετρο, ο ανεμοδείκτης και το ανεμόμετρο είχαμε σκοπό να  κατασκευαστούν με εκτυπωτή 3D όμως η πανδημία οδήγησε σε αλλαγές 2 φορές των ομάδων του έργου και έτσι αποφασίσαμε να χρησιμοποιήσουμε το σετ βροχόμετρου, ανεμόμετρου και ανεμοδεικτη, που μας έστειλαν από το το Ελλακ(Ελεύθερο Λογισμικό / Λογισμικό Ανοικτού Κώδικα)
Η αλλαγή αυτή έιχε όμως και δημιουργικά θετικά αποτελέσματα, αφού προγραμματίσαμε ένα ESP8266 να παίρνει μετρήσεις σε εσωτερικό χώρο και να τις δημοσιεύει στο διαδίκτυο στην ιστοσελίδα http://megakastro.gr/dataDisplayer.html

Αναλυτική περιγραφή ιδέας

Οι ηλεκτρονικοί  μετεωρολογικοί σταθμοί είναι πολύ χρήσιμες συσκευές και πολύ δημοφιλείς τον τελευταίο καιρό για να καταγράφουμε και να μετράμε την τοπική μας εμπειρία. Ο καιρός και το κλίμα έχουν αποκτήσει ιδιαίτερο ενδιαφέρον αφού η αναμφισβήτητη κλιματική αλλαγή μας έχει κάνει πολύ ευαίσθητους στις μετεωρολογικές αλλαγές ! Η ενσωμάτωση των πτυχών των καιρικών συνθηκών στο διαδίκτυο είναι επίσης όλο και πιο σημαντική, αφού όλο και περισσότεροι άνθρωποι θέλουν να αντλούν πληροφορίες για το πώς εξελίσσεται ο καιρός σε διαφορετικούς τόπους. Η παρακολούθηση των περιβαλλοντικών - μετεωρολογικών παραμέτρων θα δώσει τη δυνατότητα στους μαθητές να γνωρίσουν την εφαρμογή των νόμων της Φυσικής στο μετεωρολογικό γίγνεσθαι  και στους τρόπους και τα όργανα που χρησιμοποιούμε για τη μέτρηση των παραμέτρων που δημιουργούν τον καιρό.
Για τους λόγους αυτούς η κατασκευή και λειτουργία ενός ηλεκτρονικού  μετεωρολογικού σταθμού αποτελεί στόχο που αποφασίσαμε να υλοποιήσουμε.
Η λειτουργία των βροχομέτρου, ανεμομέτρου, ανεμοδείκτη θα στηριχτεί σε διακόπτες Reed που θα ενεργοποιούνται από μαγνήτες Νεοδυμίου. Τα υπόλοιπα ηλεκτρονικά όργανα θα τα προμηθευτούμε από κατασκευαστές σε χαμηλή τιμή αλλά με καλές επιδόσεις (θερμόμετρο, βαρόμετρο , υγρόμετρο και φωτοαντιστάτη). Τα όργανα αυτά θα συνδεθούν σε Arduino με WiFi, ώστε οι μετρήσεις να μπορούν να μεταδοθούν στο διαδίκτυο και να αποθηκευτούν. Το έργο αυτό θα δώσει τη δυνατότητα στους μαθητές να συμμετέχουν σε πολλαπλές δράσεις, να αναπτύξουν δεξιότητες σε θεωρητικούς, σχεδιαστικούς,  κατασκευαστικούς τομείς και να κατανοήσουν την κλιματική αλλαγή μέσα από τις μετρήσεις που θα πραγματοποιηθούν. Προσδοκούμε, υλοποιώντας και συστηματοποιώντας το έργο αυτό, να δώσουμε την δυνατότητα της αναπαραγωγής του σε άλλα σχολεία. 

Λίστα προτεινόμενου εξοπλισμού 

Arduino Uno ή Mega με WiFi για μετάδοση των δεδομένων στο δίκτυο
Τροφοδοσία 9 Volt για Arduino και αισθητήρες
misol βροχόμετρο,ανεμόμετρο,ανεμοδείκτης
αισθητήρας έντασης φωτός
οθόνη oled
Καλώδια για την ένωση των εξαρτημάτων
BMΕ280 Βαρόμετρο, Θερμόμετρο,Υγρασιόμετρο (I2C)
αισθητήρας dht11 ή 22
Πλαστικοί σωλήνες για κάλυψη καλωδίων
