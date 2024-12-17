import SwiftUI

struct SensorData: Codable {
    var humidity: Float
    var temperatureC: Float
    var heatIndexC: Float
}

struct ContentView: View {
    @State private var sensorData: SensorData?
    @State private var errorMessage: String?
    @State private var showAlert: Bool = false
    @State private var currentTab: Int = 0
    
    @Environment(\.colorScheme) var colorScheme

    func fetchData() {
        guard let url = URL(string: "http://espurlhere/data") else {
            showErrorMessage("Invalid URL")
            return
        }
        
        URLSession.shared.dataTask(with: url) { data, response, error in
            if let error = error {
                showErrorMessage("Failed to fetch data: \(error.localizedDescription)")
                return
            }
            
            guard let data = data else {
                showErrorMessage("No data received")
                return
            }
            
            let decoder = JSONDecoder()
            do {
                let decodedData = try decoder.decode(SensorData.self, from: data)
                DispatchQueue.main.async {
                    withAnimation(.easeInOut) {
                        sensorData = decodedData
                    }
                    errorMessage = nil
                }
            } catch {
                showErrorMessage("Failed to decode JSON: \(error.localizedDescription)")
            }
        }.resume()
    }

    func showErrorMessage(_ message: String) {
        DispatchQueue.main.asyncAfter(deadline: .now() + 5) {
            errorMessage = message
            showAlert = true
        }
    }
    
    func getBackgroundColor(for temperature: Float) -> Color {
        switch temperature {
        case ..<0:
            return Color.blue
        case 0..<10:
            return Color.cyan
        case 10..<20:
            return Color.green
        case 20..<30:
            return Color.orange
        default:
            return Color.red
        }
    }
    
    var body: some View {
        ZStack {
            if currentTab == 0 {
                Color.blue.edgesIgnoringSafeArea(.all)
            } else if currentTab == 1 {
                getBackgroundColor(for: sensorData?.temperatureC ?? 0)
                    .edgesIgnoringSafeArea(.all)
            } else {
                getBackgroundColor(for: sensorData?.heatIndexC ?? 0)
                    .edgesIgnoringSafeArea(.all)
            }
            
            VStack {
                TabView(selection: $currentTab) {
                    VStack {
                        if let sensorData = sensorData {
                            Text("Humidity: \(sensorData.humidity, specifier: "%.1f")%")
                                .font(.system(size: 28, weight: .bold))
                                .padding()
                                .frame(maxWidth: .infinity)
                                .background(colorScheme == .dark ? Color.black.opacity(0.8) : Color.white)
                                .foregroundColor(colorScheme == .dark ? .white : .black)
                                .cornerRadius(8)
                                .padding(.horizontal)
                        } else {
                            Text("Loading data...")
                                .font(.system(size: 28, weight: .bold))
                                .foregroundColor(.white)
                                .padding()
                        }
                        refreshButton
                    }
                    .tag(0)

                    VStack {
                        if let sensorData = sensorData {
                            Text("Temperature: \(sensorData.temperatureC, specifier: "%.1f")°C")
                                .font(.system(size: 28, weight: .bold))
                                .padding()
                                .frame(maxWidth: .infinity)
                                .background(colorScheme == .dark ? Color.black.opacity(0.8) : Color.white)
                                .foregroundColor(colorScheme == .dark ? .white : .black)
                                .cornerRadius(8)
                                .padding(.horizontal)
                        } else {
                            Text("Loading data...")
                                .font(.system(size: 28, weight: .bold))
                                .foregroundColor(.white)
                                .padding()
                        }
                        refreshButton
                    }
                    .tag(1)

                    VStack {
                        if let sensorData = sensorData {
                            Text("Heat Index: \(sensorData.heatIndexC, specifier: "%.1f")°C")
                                .font(.system(size: 28, weight: .bold))
                                .padding()
                                .frame(maxWidth: .infinity)
                                .background(colorScheme == .dark ? Color.black.opacity(0.8) : Color.white)
                                .foregroundColor(colorScheme == .dark ? .white : .black)
                                .cornerRadius(8)
                                .padding(.horizontal)
                        } else {
                            Text("Loading data...")
                                .font(.system(size: 28, weight: .bold))
                                .foregroundColor(.white)
                                .padding()
                        }
                        refreshButton
                    }
                    .tag(2)
                }
                .tabViewStyle(PageTabViewStyle(indexDisplayMode: .always))
            }
            .onAppear {
                fetchData()
            }
        }
        .animation(.easeInOut, value: currentTab)
        .alert(isPresented: $showAlert) {
            Alert(title: Text("Error"), message: Text(errorMessage ?? "Unknown error"), dismissButton: .default(Text("OK")))
        }
    }

    var refreshButton: some View {
        Button(action: fetchData) {
            Text("Refresh Data")
                .font(.system(size: 18, weight: .bold, design: .rounded))
                .padding(15)
                .background(colorScheme == .dark ? Color.black.opacity(0.8) : Color.white)
                .foregroundColor(colorScheme == .dark ? .white : .black)
                .cornerRadius(8)
        }
        .padding()
    }
}

#Preview {
    ContentView()
}
