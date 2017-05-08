//
// MainPage.xaml.h
// Déclaration de la classe MainPage.
//

#pragma once

#include "MainPage.g.h"
#include <windows.h>
//#include "MainClass.h"

using namespace Windows::UI::Xaml::Controls;


namespace ProjetSEP
{
	/// <summary>
	/// Une page vide peut être utilisée seule ou constituer une page de destination au sein d'un frame.
	/// </summary>
	public ref class MainPage sealed
	{
	public:
		MainPage();

	protected:
		virtual void OnNavigatedTo(Windows::UI::Xaml::Navigation::NavigationEventArgs^ e) override;

	private:

		//static DWORD WINAPI actualizeDisplay(MainPage^ page);
		//void ChronoThreadProc();
		void startButton_Click(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e);
		void initializeButton_Click(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e);
		void getPositionButton_Click(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e);
		//MainClass* mainThreadHandling;
		void startChronoThread();
		static void ChronoThreadProc();
		/*void startGPSThread();
		static void GPSThreadProc();*/
		//void startActualizeDisplay();
		//static void ActualizeDisplay(MainPage^ page);
		void actualize(Platform::Object^ sender, Platform::Object^ e);
		//void waitForActualize();
		//void CALLBACK actualize(HWND hwnd, UINT uMsg, UINT timerId, DWORD dwTime);
	};
}
