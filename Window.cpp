#include <iostream>
#include <Windows.h>
#include <Windowsx.h>
using namespace std;

#define BUTTON_1 1
#define BUTTON_2 2
#define BUTTON_3 3
#define BUTTON_4 4
         //hangi pencereden geldi   //pencereye ne oldu t�kland�,kapat�ld� //hangi eleman pencerenin neresi // mesajla ilgili ek bilgiler
LRESULT CALLBACK WndProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)   //wparam mesaj�n hangi butona ait oldu�unu i�erir
{
    switch (message)  //mesaj� filtrelemek i�in switch yap�s�
    {
    case WM_COMMAND: //ekrandaki nesnelerin msjlar� vm_command olarak gelir.
    	
    	switch (LOWORD(wParam)) //son 2 bayt�n� (16 bit) al�yoruz
    	{
    		case BUTTON_1:
    			MessageBox(hwnd, "Buton 1'e t�kland�.", "Buton 1 baslik?", MB_ICONINFORMATION | MB_OK);
    			break;
    			
    		case BUTTON_2:
    			MessageBox(hwnd, "Buton 2'ye t�kland�.", "Buton 2 baslik?", MB_OK);
    			break;
    			
    		case BUTTON_3:
    			SetWindowText(GetDlgItem(hwnd, LOWORD(wParam)), "T�kland�");
				break;
				
			case BUTTON_4:
    			MessageBox(hwnd, "Buton 4'e t�kland�.", "Buton 3 baslik?", MB_OK);
    			break;
		}
		
		break;
	case WM_DESTROY: 
		PostQuitMessage(0); 
		break;  //pencere kapat�ld� mesaj� gelince programa kendini kapatmas�n� s�yle. parametre 0 bir sorun yok demek.
    
	default: 
		break;
    }


    return DefWindowProc(hwnd, message, wParam, lParam); //biz bir �ey yapmazsak sistem kendisi i�lesin
}

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpszArgument, int nCmdShow)
{
	HWND hwnd;				/* Program ana penceresi i�in handle de�eri */
    WNDCLASSEX wc;			/* Program ana pencere s�n�f�na ait veri yap�s� */
    MSG msg; 				/* Program ana penceresine g�nderilen mesajlar�n kaydedildi�i de�i�ken */
    
    
    	/* Program ana pencere s�n�f� veri yap�s�na de�er atama */ 
    wc.lpszClassName = "PencereSinifi";
    wc.hInstance = hInstance;   // Pencerenin �al��aca�� uygulama �rne�i: ba�lam
    wc.lpfnWndProc = WndProc;      // Pencere mesajlar�n� i�leyecek fonksiyon.
    wc.cbSize = sizeof(WNDCLASSEX);    //S�n�f�n bellekte kaplad��� alan
	   
	   /* �n tan�ml� ikon ve mouse imlecinin kullan�lmas�n� sa�lama */
    wc.hbrBackground = (HBRUSH)COLOR_WINDOW;    //Arkaplan rengi: Standart pencere rengi
    wc.hCursor = LoadCursor(NULL, IDI_APPLICATION);  //Fare imleci: Standart  IDC_ARROW = 32512
    wc.hIcon = LoadIcon(hInstance, MAKEINTRESOURCE(32512));   //Uygulama simgesi: Varsay�lan IDI_APPLICATION = 32512
    wc.hIconSm = LoadIcon(hInstance, MAKEINTRESOURCE(32512)); //Uygulama simgesi (k���k): Varsay�lan IDI_APPLICATION =32512
    wc.lpszMenuName = NULL; //pencere men�s�: yok
    wc.cbClsExtra = 0;  //pencere ekstralar�: yok
    wc.cbWndExtra = 0;  //pencere ekstralar�: yok
    wc.style = CS_VREDRAW | CS_HREDRAW | CS_DBLCLKS; //pencere stili: Normal
    
        /* Pencere s�nf�n� kaydettik. */
    RegisterClassEx(&wc);  

        //windows penceresi olu�turma //
    hwnd = CreateWindow("PencereSinifi", "Pencere Ba�l���",    //hwnd( windows handle) pencere adresidir.
        WS_OVERLAPPEDWINDOW, 100, 100, 600 ,400, NULL, NULL, hInstance, NULL); //win pencere simgeleri X [] : k�e�erden uzakl�klar x 100 ,y 100, pencere geni�li�i 600 ,y�kseklik 400, bu bir alt pencereyse hangi pencereye ba�l� NULL, pencere men�s� NULL, program �rne�i hangi ba�lamda �al���yoruz, ek bilgiler parameterel NUll
        
    ShowWindow(hwnd, nCmdShow); //pencereyi ekranda g�sterme

	CreateWindow("BUTTON", "Buton 1", WS_CHILD | WS_VISIBLE, 10, 10, 200, 30, hwnd, (HMENU)BUTTON_1, hInstance, NULL);  // pencere s�n�f�, �zerindeki yaz�, bir pencerinin i�erisindde g�r�lecek : ws_child, ekranda g�r�n�r olacak,soldan 10, �stten 10,geni�lik, y�kseklik, hwnd penceresinin i�inde, buton kimlik numaras� (HMENU) 1,program �rne�i ba�lam, ek bilgi NULL
	CreateWindow("BUTTON", "Buton 2", WS_CHILD | WS_VISIBLE, 10, 50, 200, 30, hwnd, (HMENU)BUTTON_2, hInstance, NULL);
	CreateWindow("BUTTON", "Buton 3", WS_CHILD | WS_VISIBLE, 220, 10, 200, 30, hwnd, (HMENU)BUTTON_3, hInstance, NULL);
	CreateWindow("BUTTON", "Buton 4", WS_CHILD | WS_VISIBLE, 220, 50, 200, 30, hwnd, (HMENU)BUTTON_4, hInstance, NULL);
       
	   //mesajlar�n s�rekli kontrol edilip i�lenmesi i�in mesaj d�ng�s�.
    while(GetMessage(&msg, NULL, 0, 0))      //de�i�kenin adresi, hangi pencerenin mesajlar� : NUll yani hepsi, yaln�zca �u mesajlar� al null veya 0 hepsi.
    {
        TranslateMessage(&msg); /* Sanal tu� mesajlar�n� karakter mesajlar�na �evirir. */
        DispatchMessage(&msg);  /* Mesajlar� WndProc fonksiyonuna g�nderir. */
    }

	return msg.wParam;
}


