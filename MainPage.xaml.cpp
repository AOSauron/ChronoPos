//
// MainPage.xaml.cpp
// Implémentation de la classe MainPage.
//



#include "pch.h"
#include "MainPage.xaml.h"

#include <windows.h>
#include <tchar.h>
#include <mutex>
#include <thread>
#include <chrono>
//#include "stdfax.h"
#include <future>

using namespace ProjetSEP;

using namespace std;
using namespace Platform;
using namespace Windows::Foundation;
using namespace Windows::Foundation::Collections;
using namespace Windows::UI::Xaml;
using namespace Windows::UI::Xaml::Controls;
using namespace Windows::UI::Xaml::Controls::Primitives;
using namespace Windows::UI::Xaml::Data;
using namespace Windows::UI::Xaml::Input;
using namespace Windows::UI::Xaml::Media;
using namespace Windows::UI::Xaml::Navigation;
using namespace Windows::Devices::Geolocation;
using namespace Windows::UI::Core;


// Pour en savoir plus sur le modèle d'élément Page vierge, consultez la page http://go.microsoft.com/fwlink/?LinkId=234238

//void ChronoThreadProc();
//void actualizeDisplay(TextBlock^ chronoValue);

int hours, minutes, seconds;
int running;
int canBeActualized;
std::mutex chrono_mutex;
//Geolocator ^geolocator;
String ^positionString;

/*
template <typename... ParamTypes>
void setTimeOut(int milliseconds, std::function<void(ParamTypes...)> func, ParamTypes... parames)
{
	std::async(std::launch::async, [=]()
	{
		while (1) {
			Sleep(milliseconds);
			func(parames...);
		}
	});
};*/




MainPage::MainPage()
{
	//mainThreadHandling = new MainClass();
	running = 0;
	hours = 0; minutes = 0; seconds = 0;
	canBeActualized = 0;
	//geolocator = ref new Geolocator();
	positionString = "Nan";

	/*std::mutex locker;
	std::function<void()> actualizeDisplay = [&]()
	{
		chrono_mutex.lock();
		chronoValue->Text = hours + ":" + minutes + ":" + seconds;
		std::unique_lock<std::mutex> lk(locker);
		//std::cout << "func 3 is trigged:" << "   int: " << param1 << ";  string: " << param2 << std::endl;
		//lk.unlock();
		chrono_mutex.unlock();
	};

	for (int index = 0; index < 100; index++) {
		std::unique_lock<std::mutex> lk3(locker);
		lk3.unlock();
		setTimeOut<>(1000, actualizeDisplay);
	}
	*/
	InitializeComponent();


}

/// <summary>
/// Invoqué lorsque cette page est sur le point d'être affichée dans un frame.
/// </summary>
/// <param name="e">Données d'événement décrivant la manière dont l'utilisateur a accédé à cette page.  La propriété Parameter
/// est généralement utilisée pour configurer la page.</param>
void MainPage::OnNavigatedTo(NavigationEventArgs^ e)
{
	(void) e;	// Paramètre non utilisé
	

	// TODO: préparer la page pour affichage ici.

	// TODO: si votre application comporte plusieurs pages, assurez-vous que vous
	// gérez le bouton Retour physique en vous inscrivant à l’événement
	// Événement Windows::Phone::UI::Input::HardwareButtons.BackPressed.
	// Si vous utilisez le NavigationHelper fourni par certains modèles,
	// cet événement est géré automatiquement.
}

void MainPage::startChronoThread() {
	running = 1;
	//std::thread chronoThread(ChronoThreadProc);
	CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)ChronoThreadProc, NULL, 0, NULL);
}

void MainPage::ChronoThreadProc()
{
	Sleep(1000);
	// Pendant que le thread principal est en attente :
	while (running) {
		
		chrono_mutex.lock();
		seconds++;
		if (seconds == 60) {
			seconds = 0;
			minutes++;
		}
		if (minutes == 60) {
			minutes = 0;
			hours++;
		}
		canBeActualized = 1;
		chrono_mutex.unlock();
		Sleep(1000);
	}
}
/*
void CALLBACK ProjetSEP::MainPage::actualize(HWND hwnd, UINT uMsg, UINT timerId, DWORD dwTime) {
	chronoValue->Text = hours + ":" + minutes + ":" + seconds;
}*/



/*void MainPage::startGPSThread() {
	running = 1;
	//std::thread chronoThread(ChronoThreadProc);
	CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)GPSThreadProc, NULL, 0, NULL);
}*/

/*void MainPage::GPSThreadProc() {
	IAsyncOperation<Geoposition ^> ^asyncPos = geolocator->GetGeopositionAsync();

	Geoposition ^position = await geolocator.GetGeopositionAsync();
	try {
		position = asyncPos->GetResults();


		positionString = position->Coordinate->Latitude.ToString() + " - " + position->Coordinate->Longitude.ToString();
	}
	catch (Platform::Exception^ ex) {

	}
}*/



void MainPage::actualize(Platform::Object^ sender, Platform::Object^ e) {
	String ^hourString;
	String ^minuteString;
	String ^secondString;
	if (hours < 10) {
		hourString = "0" + hours.ToString();
	}
	else {
		hourString = hours.ToString();
	}
	if (minutes < 10) {
		minuteString = "0" + minutes.ToString();
	}
	else {
		minuteString = minutes.ToString();
	}
	if (seconds < 10) {
		secondString = "0" + seconds.ToString();
	}
	else {
		secondString = seconds.ToString();
	}

	chronoValue->Text = hourString + ":" + minuteString + ":" + secondString;
}
/*
void MainPage::startActualizeDisplay() {
	//std::thread chronoThread(ChronoThreadProc);
	CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)ActualizeDisplay, (LPVOID)this, 0, NULL);
}*/
/*
void MainPage::ActualizeDisplay(MainPage^ page) {
	page = (MainPage^)page;
	while (running) {
		page->actualize();
	}
}*/
/*
void MainPage::waitForActualize() {
	while (1) {
		Sleep(500);
		chrono_mutex.lock();
		if (canBeActualized) {
			chronoValue->Text = hours + ":" + minutes + ":" + seconds;
			canBeActualized = 0;
		}
		chrono_mutex.unlock();
	}
}*/


void MainPage::startButton_Click(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e)
{
	DispatcherTimer^ timer = ref new DispatcherTimer;

	if (running == 0) {
		running = 1;
		startButton->Content = "Pause";
		this->startChronoThread();


		
		timer->Tick += ref new Windows::Foundation::EventHandler<Object^>(this, &MainPage::actualize);
		TimeSpan t;
		t.Duration = 100;
		timer->Interval = t;
		timer->Start();
	}
	else {
		timer->Stop();
		running = 0;
		startButton->Content = "Démarrer";
	}

	/*
	chronoThread.join();
	chronoThread.join();
	*/
}


void MainPage::initializeButton_Click(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e)
{
	running = 0;
	hours = 0;
	minutes = 0;
	seconds = 0;
	chronoValue->Text = "00:00:00";
}

 
void MainPage::getPositionButton_Click(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e) {

	String ^hourString;
	String ^minuteString;
	String ^secondString;
	if (hours < 10) {
		hourString = "0" + hours.ToString();
	}
	else {
		hourString = hours.ToString();
	}
	if (minutes < 10) {
		minuteString = "0" + minutes.ToString();
	}
	else {
		minuteString = minutes.ToString();
	}
	if (seconds < 10) {
		secondString = "0" + seconds.ToString();
	}
	else {
		secondString = seconds.ToString();
	}

	savedValues->Text = hourString + ":" + minuteString + ":" + secondString + " " + positionString + "\n" + savedValues->Text;

	
}