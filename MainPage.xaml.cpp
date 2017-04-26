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


int hours = 0, minutes = 0, seconds = 0;
std::mutex chrono_mutex;


MainPage::MainPage()
{
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


void ProjetSEP::MainPage::displayActualize() {
	//TextBlock chronoValue = new TextBlock;//hours+":"+minutes+":"+seconds;
	chronoValue->Text = hours + ":" + minutes + ":" + seconds;
	//TextBox.Text = Replace();
}


// Procédure utilisée par le thread
DWORD WINAPI ProjetSEP::MainPage::ChronoThreadProc(MainPage^ arg)
{
	
	// Pendant que le thread principal est en attente :
	while (1) {
		Sleep(1000);

		chrono_mutex.lock();
		if (seconds == 59) {
			seconds = 0;
			minutes++;
		}
		if (minutes == 59) {
			minutes = 0;
			hours++;
		}
		chrono_mutex.unlock();

		// On actualise l'affichage
		arg->displayActualize();
	}


	// On ferme, le thread va être arrèté par le système dès que cette fonction retournera
	return 0;
}


void ProjetSEP::MainPage::startButton_Click(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e)
{
	//ThreadStart *myThreadDelegate = new ThreadStart(this, running);
	//Thread *trd = new Thread(myThreadDelegate);
	//CWinThread *m_pthread[5];
	//DWORD ThreadId;
	// On démarre le thread. ThreadId est l'identifiant du thread
	// ThreadId ne nous est d'aucune utilité dans cet exmple car le thread se termine de lui même
	//CreateThread(NULL, NULL, (LPTHREAD_START_ROUTINE) ChronoThreadProc, (LPVOID)this, 0, &ThreadId);

	std::thread chronoThread(ChronoThreadProc, this);
	
	chronoThread.join();
}


void ProjetSEP::MainPage::button2_Click(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e)
{

}



void ProjetSEP::MainPage::textBlock1_SelectionChanged(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e)
{

}


void ProjetSEP::MainPage::textBlock_SelectionChanged(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e)
{

}
