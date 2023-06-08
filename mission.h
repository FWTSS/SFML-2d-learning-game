/////////////////////////////////����� ������ //////////////////////////////////////

int getCurrentMission(int x) //������� ������ ������, ������� ������ ����� ������ � ����������� �� ���������� X ������(���� ����� ���������� ��� ����������)
{
	int mission = 0;

	if ((x > 0) && (x < 600)) { mission = 0; } // �������� ������ � �����
	if (x > 400) { mission = 1; }// ����� �� ������ ������
	if (x > 700) { mission = 2; }// ����� �� ������ ������
	if (x > 2200) { mission = 3; } // ����� �� ������� ������

	return mission; // ������� ���������� ����� ������
}

///////////////////////////����� ������ ///////////////////////////////////////////
std::string getTextMission(int currentMission)
{
	std::string missionText = ""; // ����� ������ � ��� �������������

	switch (currentMission)// ����������� ����� ������ � � ����������� �� ���� ���������� missionText ������������� ��������� �����
	{
	case 0: missionText = "\nFirst stage and \ninstructions for game"; break;
	case 1: missionText = "\nMission 1\n\nIt is your first\n mission, on\n this stage \nbe careful\n ... and so on..."; break;
	case 2: missionText = "\nMission 2\n You must solve \n logic task,\n that you are able to go "; break;
	case 3: missionText = "\nand so on  \nand so on so o..."; break;


	}

	return missionText;

}