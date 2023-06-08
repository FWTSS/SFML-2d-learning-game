/////////////////////////////////НОМЕР МИССИИ //////////////////////////////////////

int getCurrentMission(int x) //функция номера миссии, которая меняет номер миссии в зависимости от координаты X игрока(сюда будем передавать эту координату)
{
	int mission = 0;

	if ((x > 0) && (x < 600)) { mission = 0; } // знакомим игрока с игрой
	if (x > 400) { mission = 1; }// игрок на первой миссии
	if (x > 700) { mission = 2; }// игрок на второй миссии
	if (x > 2200) { mission = 3; } // игрок на третьей миссии

	return mission; // функция возвращает номер миссии
}

///////////////////////////ТЕКСТ МИССИИ ///////////////////////////////////////////
std::string getTextMission(int currentMission)
{
	std::string missionText = ""; // текст миссии и его инициализация

	switch (currentMission)// принимается номер миссии и в зависимости от него переменной missionText присваивается различный текст
	{
	case 0: missionText = "\nFirst stage and \ninstructions for game"; break;
	case 1: missionText = "\nMission 1\n\nIt is your first\n mission, on\n this stage \nbe careful\n ... and so on..."; break;
	case 2: missionText = "\nMission 2\n You must solve \n logic task,\n that you are able to go "; break;
	case 3: missionText = "\nand so on  \nand so on so o..."; break;


	}

	return missionText;

}