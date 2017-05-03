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

using namespace ProjetSEP;

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

// Pour en savoir plus sur le modèle d'élément Page vierge, consultez la page http://go.microsoft.com/fwlink/?LinkId=234238

//void ChronoThreadProc();
//void actualizeDisplay(TextBlock^ chronoValue);

int hours, minutes, seconds;
int running;
std::mutex chrono_mutex;


MainPage::MainPage()
{
	//mainThreadHandling = new MainClass();
	running = 0;
	hours = 0; minutes = 0; seconds = 0;
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
	chronoValue->Text = hours+":"+minutes+":"+seconds;

	// TODO: préparer la page pour affichage ici.

	// TODO: si votre application comporte plusieurs pages, assurez-vous que vous
	// gérez le bouton Retour physique en vous inscrivant à l’événement
	// Événement Windows::Phone::UI::Input::HardwareButtons.BackPressed.
	// Si vous utilisez le NavigationHelper fourni par certains modèles,
	// cet événement est géré automatiquement.
}

void ProjetSEP::MainPage::startChronoThread() {
	running = 1;
	//std::thread chronoThread(ChronoThreadProc);
	CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)ChronoThreadProc, NULL, 0, NULL);
}

void ProjetSEP::MainPage::ChronoThreadProc()
{

	// Pendant que le thread principal est en attente :
	while (running) {
		Sleep(1000);

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
		running = 0;
		chrono_mutex.unlock();

	}
}



void ProjetSEP::MainPage::startButton_Click(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e)
{
	//mainThreadHandling->setRunning();
	running = 1;
	this->startChronoThread();
	//mainThreadHandling->startactualizeDisplayThread(chronoValue);

	/*
	chronoThread.join();
	chronoThread.join();
	*/
}


void ProjetSEP::MainPage::button2_Click(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e)
{
	//mainThreadHandling->setNotRunning();
	running = 0;
}



void ProjetSEP::MainPage::textBlock1_SelectionChanged(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e)
{

}


void ProjetSEP::MainPage::textBlock_SelectionChanged(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e)
{

}
