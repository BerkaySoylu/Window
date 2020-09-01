#include <iostream>
#include <Windows.h>
#include <Windowsx.h>
using namespace std;

#define BUTTON_1 1
#define BUTTON_2 2
#define BUTTON_3 3
#define BUTTON_4 4
         //hangi pencereden geldi   //pencereye ne oldu týklandý,kapatýldý //hangi eleman pencerenin neresi // mesajla ilgili ek bilgiler
LRESULT CALLBACK WndProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)   //wparam mesajýn hangi butona ait olduðunu içerir
{
    switch (message)  //mesajý filtrelemek için switch yapýsý
    {
    case WM_COMMAND: //ekrandaki nesnelerin msjlarý vm_command olarak gelir.
    	
    	switch (LOWORD(wParam)) //son 2 baytýný (16 bit) alýyoruz
    	{
    		case BUTTON_1:
    			MessageBox(hwnd, "Buton 1'e týklandý.", "Buton 1 baslik?", MB_ICONINFORMATION | MB_OK);
    			break;
    			
    		case BUTTON_2:
    			MessageBox(hwnd, "Buton 2'ye týklandý.", "Buton 2 baslik?", MB_OK);
    			break;
    			
    		case BUTTON_3:
    			SetWindowText(GetDlgItem(hwnd, LOWORD(wParam)), "Týklandý");
				break;
				
			case BUTTON_4:
    			MessageBox(hwnd, "Buton 4'e týklandý.", "Buton 3 baslik?", MB_OK);
    			break;
		}
		
		break;
	case WM_DESTROY: 
		PostQuitMessage(0); 
		break;  //pencere kapatýldý mesajý gelince programa kendini kapatmasýný söyle. parametre 0 bir sorun yok demek.
    
	default: 
		break;
    }


    return DefWindowProc(hwnd, message, wParam, lParam); //biz bir þey yapmazsak sistem kendisi iþlesin
}

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpszArgument, int nCmdShow)
{
	HWND hwnd;				/* Program ana penceresi için handle deðeri */
    WNDCLASSEX wc;			/* Program ana pencere sýnýfýna ait veri yapýsý */
    MSG msg; 				/* Program ana penceresine gönderilen mesajlarýn kaydedildiði deðiþken */
    
    
    	/* Program ana pencere sýnýfý veri yapýsýna deðer atama */ 
    wc.lpszClassName = "PencereSinifi";
    wc.hInstance = hInstance;   // Pencerenin çalýþacaðý uygulama örneði: baðlam
    wc.lpfnWndProc = WndProc;      // Pencere mesajlarýný iþleyecek fonksiyon.
    wc.cbSize = sizeof(WNDCLASSEX);    //Sýnýfýn bellekte kapladýðý alan
	   
	   /* Ön tanýmlý ikon ve mouse imlecinin kullanýlmasýný saðlama */
    wc.hbrBackground = (HBRUSH)COLOR_WINDOW;    //Arkaplan rengi: Standart pencere rengi
    wc.hCursor = LoadCursor(NULL, IDI_APPLICATION);  //Fare imleci: Standart  IDC_ARROW = 32512
    wc.hIcon = LoadIcon(hInstance, MAKEINTRESOURCE(32512));   //Uygulama simgesi: Varsayýlan IDI_APPLICATION = 32512
    wc.hIconSm = LoadIcon(hInstance, MAKEINTRESOURCE(32512)); //Uygulama simgesi (küçük): Varsayýlan IDI_APPLICATION =32512
    wc.lpszMenuName = NULL; //pencere menüsü: yok
    wc.cbClsExtra = 0;  //pencere ekstralarý: yok
    wc.cbWndExtra = 0;  //pencere ekstralarý: yok
    wc.style = CS_VREDRAW | CS_HREDRAW | CS_DBLCLKS; //pencere stili: Normal
    
        /* Pencere sýnfýný kaydettik. */
    RegisterClassEx(&wc);  

        //windows penceresi oluþturma //
    hwnd = CreateWindow("PencereSinifi", "Pencere Baþlýðý",    //hwnd( windows handle) pencere adresidir.
        WS_OVERLAPPEDWINDOW, 100, 100, 600 ,400, NULL, NULL, hInstance, NULL); //win pencere simgeleri X [] : köeþerden uzaklýklar x 100 ,y 100, pencere geniþliði 600 ,yükseklik 400, bu bir alt pencereyse hangi pencereye baðlý NULL, pencere menüsü NULL, program örneði hangi baðlamda çalýþýyoruz, ek bilgiler parameterel NUll
        
    ShowWindow(hwnd, nCmdShow); //pencereyi ekranda gösterme

	CreateWindow("BUTTON", "Buton 1", WS_CHILD | WS_VISIBLE, 10, 10, 200, 30, hwnd, (HMENU)BUTTON_1, hInstance, NULL);  // pencere sýnýfý, üzerindeki yazý, bir pencerinin içerisindde görülecek : ws_child, ekranda görünür olacak,soldan 10, üstten 10,geniþlik, yükseklik, hwnd penceresinin içinde, buton kimlik numarasý (HMENU) 1,program örneði baðlam, ek bilgi NULL
	CreateWindow("BUTTON", "Buton 2", WS_CHILD | WS_VISIBLE, 10, 50, 200, 30, hwnd, (HMENU)BUTTON_2, hInstance, NULL);
	CreateWindow("BUTTON", "Buton 3", WS_CHILD | WS_VISIBLE, 220, 10, 200, 30, hwnd, (HMENU)BUTTON_3, hInstance, NULL);
	CreateWindow("BUTTON", "Buton 4", WS_CHILD | WS_VISIBLE, 220, 50, 200, 30, hwnd, (HMENU)BUTTON_4, hInstance, NULL);
       
	   //mesajlarýn sürekli kontrol edilip iþlenmesi için mesaj döngüsü.
    while(GetMessage(&msg, NULL, 0, 0))      //deðiþkenin adresi, hangi pencerenin mesajlarý : NUll yani hepsi, yalnýzca þu mesajlarý al null veya 0 hepsi.
    {
        TranslateMessage(&msg); /* Sanal tuþ mesajlarýný karakter mesajlarýna çevirir. */
        DispatchMessage(&msg);  /* Mesajlarý WndProc fonksiyonuna gönderir. */
    }

	return msg.wParam;
}


