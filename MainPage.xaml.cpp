﻿//
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
using namespace Windows::System;
using namespace Windows::System::Display;


// Pour en savoir plus sur le modèle d'élément Page vierge, consultez la page http://go.microsoft.com/fwlink/?LinkId=234238


int hours, minutes, seconds;
int running;
int canBeActualized;
std::mutex chrono_mutex;
std::mutex gps_mutex;
String ^positionString;




MainPage::MainPage()
{
	running = 0;
	hours = 0; minutes = 0; seconds = 0;
	canBeActualized = 0;
	positionString = "";

	InitializeComponent();

	startGPSThread();
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
	CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)ChronoThreadProc, NULL, 0, NULL);
}

void MainPage::ChronoThreadProc()
{
	Sleep(1000);
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

void MainPage::startGPSThread() {
	CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)GPSThreadProc, NULL, 0, NULL);
}

void MainPage::GPSThreadProc()
{
	while (1) {
		int accuracyInMeters = 5;
		IAsyncOperation<Geoposition^>^ m_getOperation;

		Geolocator^ geolocator = ref new Geolocator();

		geolocator->DesiredAccuracyInMeters = (Platform::IBox<UINT>^)(PropertyValue::CreateUInt32(accuracyInMeters));

		m_getOperation = geolocator->GetGeopositionAsync();

		// Start location acquisition.
		// Setting the completion callback implicitly starts acquisition.
		m_getOperation->Completed = ref new AsyncOperationCompletedHandler<Geoposition^>(
			[=](IAsyncOperation<Geoposition^>^ asyncOperation, AsyncStatus status) mutable
		{
			if (status != AsyncStatus::Error)
			{
				Geoposition^ geoposition = asyncOperation->GetResults();

				// use the location information
				double latitude = geoposition->Coordinate->Latitude;
				double longitude = geoposition->Coordinate->Longitude;
				double accuracy = geoposition->Coordinate->Accuracy;

				//positionString = "Lat. " + latitude + ", Long. " + longitude + ", Précision = " + accuracy;
				gps_mutex.lock();
				positionString = "(" + latitude + " ; " + longitude + ")";//"Lat. " + latitude + ", Long. " + longitude;
				gps_mutex.unlock();
			}
			else
			{
				if (asyncOperation->ErrorCode.Value == E_ABORT)
				{
					//positionString = "GPS DESACTIVE";
					// The user has disable location in the phone settings
					// Printer : Activer les GPS pour acquisition
					perror("Le GPS est desactivé");
				}
				else
				{
					// L EMULATION SORT ICI !!!!!!
					positionString = "ERREUR GPS";
					// There was another error
					// Printer : une erreur est survenue avec le GPS
					perror("Une erreur est survenue avec le GPS");
				}
			}
		});
	}
}



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

}


void MainPage::initializeButton_Click(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e)
{
	running = 0;
	hours = 0;
	minutes = 0;
	seconds = 0;
	chronoValue->Text = "00:00:00";
	startButton->Content = "Démarrer";
	savedValues->Text = "";
	positionString = "Nan";
}

 
void MainPage::getPositionButton_Click(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e) {
	if (positionString != "") {
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

		//positionString = "\n Lat. 2566\n Long. 3648";

		String^ temp = savedValues->Text;
		gps_mutex.lock();
		savedValues->Text = hourString + ":" + minuteString + ":" + secondString + "\n" + positionString + "\n" + temp;
		gps_mutex.unlock();
	}
}