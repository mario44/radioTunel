<script>
teraz=new Date()
dn=teraz.getDate()
tyg=teraz.getDay()
miech=(teraz.getMonth() + 1)
rok=(teraz.getYear()+1900)

if(tyg==0){tyg="niedziela"}
if(tyg==1){tyg="poniedzałek"}
if(tyg==2){tyg="wtorek"}
if(tyg==3){tyg="środa"}
if(tyg==4){tyg="czwartek"}
if(tyg==5){tyg="piątek"}
if(tyg==6){tyg="sobota"}




stycznia=["Masława, Mieczysława, Mieszka","Bazylego, Makarego, Narcyzy","Arlety, Danuty, Lucjana","Anieli, Elżbiety, Tytusa","Edwarda, Hanny, Szymona","Kacpra, Melchiora, Baltazara","Juliana, Lucjana, Walentyny","Artura, Rajmunda, Seweryny","Adriana, Alicji, Teresy","Ady, Jana, Wilhelma","Feliksa, Honoraty, Marty","Bernarda, Czesławy, Grety","Bogumiła, Bogumiły, Weroniki","Feliksa, Hilarego, Martyny","Arnolda, Dory, Pawła","Mascelego, Walerii, Włodzimierza","Antoniego, Henryki, Mariana","Beatrycze, Małgorzaty, Piotra","Erwiny, Henryka, Mariusza","Fabioli, Miły, Sebastiana","Agnieszki, Jarosława, Nory","Dominiki, Mateusza, Wincentego","Fernandy, Jana, Rajmundy","Felicji, Roberta, Sławy","Miłosza, Pawła, Tatiany","Lutosława, Normy, Pauliny","Anieli, Juliana, Przemysława","Agnieszki, Kariny, Lesława","Franciszka, Konstancji, Salomei","Martyny, Macieja, Teofila","Joanny, Ksawerego, Luizy"]

luty=["Brygidy, Dobrogniewa, Ignacego","Kornela, Marii, Mirosławy","Błażeja, Joanny, Telimeny","Andrzeja, Mariusza, Weroniki","Agaty, Filipa, Justyniana","Amandy, Bogdana, Doroty","Ryszarda, Teodora, Wilhelminy","Irminy, Piotra, Sylwii","Bernarda, Eryki, Rajmunda","Elwiry, Elizy, Jacka","Bernadetty, Marii, Olgierda","Czasława, Damiana, Normy","Grzegorza, Lesława, Katarzyny","Liliany, Walentyny, Walentego","Arnolda, Jowity, Georginy","Danuty, Daniela, Juliany","Donata, Gizeli, Łukasza","Konstancji, Krystiana, Sylwany","Bettiny, Konrada, Mirosława","Anety, Lehca, Leona","Eleonory, Lenki, Kiejstuta","Małgorzaty, Marty, Nikifora","Damiana, Romana, Romany","Boguty, Bogusza, Macieja","Almy, Cezarego, Jarosława","Bogumiła, Eweliny, Mirosława","Gagrieli, Liwii, Leonarda","Ludomira, Makarego, Wiliany","Lecha, Lutomira"]

marca=["Albina, Antoniny, Radosławy","Halszki, Heleny, Karola","Kingi, Maryna, Tycjana","Adrianny, Kazimierza, Wacława","Aurory, Fryderyka, Oliwii","Jordana, Marcina, Róży","Flicyty, Kajetana, Pauli","Beaty, Juliana, Wincentego","Dominika, Franciszki, Katarzyny","Bożysławy, Cypriana, Marcelego","Konstantego, Ludosława, Rozyny","Grzegorza, Justyny, Józefiny","Bożeny, Krystyny, Marka","Dalii, Leona, Matyldy","Delfiny, Longina, Ludwiki","Izabeli, Henryka, Oktawii","Reginy, Patryka, Zdyszka","Edwarda, Narcyza, Zbysława","Aleksandryny, Józefa, Nicety","Joachima, Kiry, Maurycego","Benedykta, Lubomiry, Lubomira","Bogusława, Jagody, Katarzyny","Feliksa, Konrada, Zbysławy","Gabrieli, Marka, Seweryna","Bolka, Cezaryny, Marioli","Dory, Olgi, Teodora","Ernesta, Jana, Marka","Anieli, Kasrota, Soni","Marka, Wiktoryny, Zenona","Amelii, Dobromira, Leonarda","Balbiny, Kamila, Kornelii"]

kwietnia=["Chryzamtyny, Grażyny, Zygmunta","Franciszka, Malwiny, Władysława","Pankracego, Renaty, Ryszarda","Benedykta, Izodory, Wacławy","Ireny, Kleofasa, Wincentego","Ady, Celestyny, Ireneusza","Donata, Herminy, Rufina","Amadeusza, Cezaryny, Juliany","Mai, Marcelego, Wadima","Borysławy, makarego, Michała","Filipa, Izoldy, Leona","Juliusza, Lubosława, Wiktoryny","Artemona, Justyny, Przemysławy","Bernarda, Martyny, Waleriana","Adolfiny, Odetty, Wacława","Bernarda, Biruty, Erwina","Anicety, Klary, Rudolfina","Apoloniusza, Bogusławy, Gościsławy","Alfa, Leonii, Tytusa","Agnieszki, Amalii, Czecha","Jarosława, Konrada, Selmy","Łukasza, Kai, Nastazji","Ilony, Jerzego, Wojciecha","Bony, Horacji, Jerzego","Jarosława, Marka, Wiki","Marii, Marzeny, Ryszarda","Sergiusza, Teofila, Zyty","Bogny, Walerii, Witalisa","Hugona, Piotra, Roberty","Balladyny, Lilli, Mariana"]

maja=["Józefa, Lubomira, Ramony","Longiny, Toli, Zygmunta","Jaropełka, Marii, Niny","Floriana, Michała, Moniki","Irydy, Tamary, Waldemara","Beniny, Filipa, Judyty","Augusta, Gizeli, Ludomiry","Kornela, Lizy, Stanisława","Grzegorza, Karoliny, Karola","Antoniny, Izydory, Jana","Igi, Mamerta, Miry","Dominika, Imeldy, Pankracego","Agnieszki, Magdaleny, Serwacego","Bonifacego, Julity, Macieja","Dionizego, Nadziei, Zofii","Andrzeja, Jędrzeja, Małgorzaty","Brunony, Sławomira, Wery","Alicji, Edwina, Eryka","Celestyny, Iwony, Piotra","Bazylego, Bernardyna, Krystyny","Jana, Moniki, Wiktora","Emila, Neleny, Romy","Leoncjusza, Michała, Renaty","Joanny, Zdenka, Zuzanny","Borysa, Magdy, Marii-Magdaleny","Eweliny, Jana, Pawła","Amandy, Jana, Juliana","Augustyna, Ingi, Jaromira","Benity, Maksymiliana, Teodozji","Ferdynanda, Gryzeldy, Zyndrama","Anieli, Feliksa, Kamili"]

czerwca=["Gracji, Jakuba, Konrada","Erazma, Marianny, Marzeny","Anatola, Leszka, Tamary","Christy, Helgi, Karola","Bonifacego, Kiry, Waltera","Laury, Laurentego, Nory","Ariadny, Jarosława, Roberta","Ady, Celii, Medarda","Anny-Marii, Felicjana, Sławoja","Bogumiła, Diany, Małgorzaty","Barnaby, Benedykta, Flory","Gwidona, Leonii, Niny","Antoniego, Gracji, Lucjana","Bazylego, Elizy, Justyny","Jolanty, Lotara, Wita","Aliny, Anety, Benona","Laury, Leszka, Marcjana","Elżbiety, Marka, Pauli","Gerwazego, Protazego, Sylwii","Bogny, Rafaeli, Rafała","Alicji, Alojzego, Rudolfa","Pauliny, Sabiny, Tomasza","Albina, Wandy, Zenona","Danuty, Jana, Janiny","Łucji, Witolda, Wilhelma","Jana, Pauliny, Rudolfiny","Cypriana, Emanueli, Władysława","Florentyny, Ligii, Leona","Pawła, Piotra, Salomei","Arnolda, Emiliany, Lucyny"]

lipca=["Bogusza, Haliny, Mariana","Kariny, Serafiny, Urbana","Anatola, Jacka, Mirosławy","Aureli, Malwiny, Zygfryda","Antoniego, Bartłomieja, Karoliny","Dominiki, Jaropełka, Łucji","Estery, Kiry, Rudolfa","Arnolda, Edgara, Elżbiety","Hieronima, Palomy, Weroniki","Filipa, Sylwany, Witalisa","Benedykta, Kariny, Olgi","Brunona, Jana, Wery","Danieli, Irwina, Małgorzaty","Kamili, Kamila, Marcelego","Henryka, Igi, Włodzimierza","Eustachego, Mariki, Mirelli","Aleksego, Bogdana, Martyny","Kamila, Karoliny, Roberta","Alfreny, Rufina, Wincentego","Fryderyka, Małgorzaty, Seweryny","Danieli, Wawrzyńca, Wiktora","Magdaleny, Mileny, Wawrzyńca","Sławy, Sławosza, Żelisławy","Kingi, Krystyna, Michaliny","jakuba, Krzysztofa, Walentyny","Anny, Mirosławy, Joachima","Aureliusza, Natalii, Rudolfa","Ady, Wiwiany, Sylwiusza","Marty, Konstantego, Olafa","Julity, Ludmiły, Zdobysława","Ignacego, Lodomiry, Romana"]

sierpnia=["Jarosława, Justyny, Nadziei","Gustawa, Kariny, Stefana","Augustyna, Kamelii, Lidii","Dominiki, Dominika, Protazego","Emila, Karoliny, Kary","Jakuba, Sławy, Wincentego","Donaty, Olechny, Kajetana","Izy, Rajmunda, Seweryna","Klary, Romana, Rozyny","Bianki, Borysa, Wawrzyńca","Luizy, Włodzmierza, Zuzanny","Hilarii, Juliana, Lecha","Elwiry, Hipolita, Radosławy","Alfreda, Maksymiliana, Selmy","Marii, napoleona, Stelii","Joachima, Nory, Stefana","Anity, Elizy, Mirona","Bogusława, Bronisława, Ilony","Emilii, Julinana, Konstancji","Bernarda, Sabiny, Samuela","Franciszka, Kazimiery, Ruty","Cezarego, Marii, Zygfryda","Apolinarego, Miły, Róży","Bartosza, Jerzego, Maliny","Belii, Ludwika, Luizy","Ireneusza, Konstantego, Marii","Cezarego, Małgorzaty, Moniki","Adeliny, Erazma, Sobiesława","Beaty, Racibora, Sabiny","Benona, Jowity, Szczęsnego","Cyrusa, Izabeli, Rajmundy"]

września=["Belindy, Bronisza, Idziego","Dionizy, Izy, Juliana","Joachima, Liliany, Szymona","Dalii, Idy, Rocha","Doroty, Justyna, Wawrzyńca","Beaty, Eugeniusza, Lidy","Reginy, Marka, Melchiora","Czcibora, Marii, Serafiny","Aldony, Jakuba, Sergiusza","Eligii, Irmy, Łukasza","Dagny, Jacka, Prota","Amadeusza, Gwidy, Sylwiny","Apolinarego, Eugenii, Lubomira","Bernarda, Mony, Roksany","Albina, Lolity, Ronalda","Jagienki, Kamili, Korneliusza","Franciszka, Lamberty, Narcyza","Ireny, Irminy, Stanisława","Januarego, Konstancji, Leopolda","Eustachego, Faustyny, Renaty","Darii, Mateusza, Wawrzyńca","Maury, Milany, Tomasza","Bogusława, Liwiusza, Tekli","Dory, Gerarda, Maryny","Aureli, Kamila, Kleofasa","Cypriana, Justyny, Łucji","Damiana, Mirabeli, Wincentego","Libuszy, Wacławy, Wacława","Michaliny, Michała, Rafała","Geraldy, Honoriusza, Wery"]

październik=["Heloizy, Igora, Remigiusza","Racheli, Sławy, Teofila","Bogumiła, Gerarda, Józefy","Edwina, Rosławy, Rozalii","Flawii, Justyna, Rajmunda","Artura, Fryderyki, Petry","Krystyna, Marii, Marka","Brygidy, Loreny, Marcina","Arnolda, Ludwika, Sybili","Franciszka, Loretty, Poli","Aldony, Brunona, Emila","Krystyny, Maksa, Serafiny","Edwarda, Geraldyny, Teofila","Alany, Damiana, Liwii","Jadwigi, Leonarda, Teresy","Ambrożego, Florentyny, Gawła","Antonii, Ignacego, Wiktora","Hanny, Klementyny, Łukasza","Michaliny, Michała, Piotra","Ireny, Kleopatry, Witalisa","Celiny, Hilarego, Janusza","Haliszki, Lody, Przybysłąwa","Edwarda, Marleny, Seweryna","Arety, Marty, Marcina","Ingi, Maurycego, Sambora","Ewarysta, Lucyny, Lutosławy","Iwony, Noemi, Szymona","Narcyza, Serafina, Wioletty","Angeli, Przemysława, Zenobii","Augustyny, Łukasza, Urbana"]

listopad=["Konrada, Seweryny, Wiktoryny","Bohdany, Henryka, Tobiasza","Huberta, Miły, Sylwii","Albertyny, Karola, Olgierda","Balladyny, Elżbiety, Sławomira","Arletty, Feliksa, Leonarda","Antoniego, Kaliny, Przemiły","Klaudii, Seweryna, Wiktoriusza","Anatolii, Gracji, Teodora","Leny, Lubomira, Natalii","Bartłomieja, Gertrudy, Marcina","Konrada, Renaty, Witolda","Arkadii, Krystyna, Stanisławy","Emila, Laury, Rogera","Amielii, Idalii, Leopolda","Edmunda, Marii, Marka","Grzegorza, Salomei, Walerii","Klaudyny, Romana, Tomasza","Elżbiety, Faustyny, Pawła","Anatola, Edyty, Rafała","Janusza, Marii, Reginy","Cecylii, Jonatana, Marka","Adeli, Felicyty, Klemensa","Emmy, Flory, Romana","Elżbiety, Katarzyny, Klemensa","Leona, Leonarda, Lesławy","Franciszka, Kseni, Maksymiliana","Jakuba, Stefana, Romy","Błażeja, Margerity, Saturnina","Andrzeja, Maury, Ondraszka"]

grudzień=["Blanki, Edmunda, Eligiusza","Balbiny, Ksawerego, Pauliny","Hilarego, Franciszki, Ksawery","Barbary, Hieronima, Krystiana","Kryspiny, Norberta, Sabiny","Dionizji, Leontyny, Mikołaja","Agaty, Dalii, Sobiesława","Delfiny, Marii, Wirginiusza","Anety, Leokadii, Wiesława","Danieli, Bohdana, Julii","Biny, Damazego, Waldemara","Ady, Aleksandra, Dagmary","Dalidy, Juliusza, Łucji","Alfreda, Izydora, Zoriny","Celiny, Ireneusza, Niny","Albiny, Sebastiana, Zdzisławy","Jolanty, Łukasza, Olimpii","Bogusława, Gracjana, Laury","Beniaminy, Dariusza, Gabrieli","Bogumiły, Dominika, Zefiryna","Honoraty, Seweryny, Tomasza","Bożeny, Drogomira, Zenona","Dagny, Sławomiry, Wiktora","Adama, Ewy, Irminy","Anety, Glorii, Piotra","Dionizego, Kaliksta, Szczepana","Fabioli, Jana, Żanety","Antoniusza, Cezarego, Teofilii","Dawida, Dionizy, Tomasza","Eugeniusza, Katarzyny, Sabiny","Mariusza, Melanii, Sylwestra"]

im=""
if(miech==1){miech="stycznia",im=stycznia[dn - 1]}
if(miech==2){miech="luty",im=luty[dn - 1]}
if(miech==3){miech="marca",im=marca[dn - 1]}
if(miech==4){miech="kwietnia",im=kwietnia[dn - 1]}
if(miech==5){miech="maja",im=maja[dn - 1]}
if(miech==6){miech="czerwca",im=czerwca[dn - 1]}
if(miech==7){miech="lipca",im=lipca[dn - 1]}
if(miech==8){miech="sierpnia",im=sierpnia[dn - 1]}
if(miech==9){miech="września",im=września[dn - 1]}
if(miech==10){miech="październik",im=październik[dn - 1]}
if(miech==11){miech="listopad",im=listopad[dn - 1]}
if(miech==12){miech="grudzień",im=grudzień[dn - 1]}

document.write("<b>  &nbsp; &nbsp;&nbsp;&nbsp;&nbsp;    Dzisiaj jest:</b> "+ tyg + ", " + dn + " " + miech +", " + rok + " roku." + "" +
"<b> Imieniny:</b> " + im + ".")
//-->

  </script>
