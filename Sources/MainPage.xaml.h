//
// MainPage.xaml.h
// Déclaration de la classe MainPage.
//

#pragma once

#include "MainPage.g.h"
#include <windows.h>

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
		void startButton_Click(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e);
		void initializeButton_Click(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e);
		void getPositionButton_Click(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e);
		void startChronoThread();
		static void ChronoThreadProc();
		void startGPSThread();
		static void GPSThreadProc();
		void actualize(Platform::Object^ sender, Platform::Object^ e);
		void appTitle_SelectionChanged();
		void savedValues1_ViewChanged();
		void actualizeDisplay(Platform::Object^ sender, Platform::Object^ e);
		void saveButton_Click(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e);
	};
}
