import pandas as pd
import numpy as np
from scipy.optimize import curve_fit
import matplotlib.pyplot as plt

def linear_model(x, a, b):
    return a * x + b

def linearithmic_model(x, a, b):
    return a * x * np.log(x + 1) + b

def fit_curve_and_plot(data):
    edges = data['Edges']
    times = data['Kruskal']

    # Fit the linear model
    linear_params, _ = curve_fit(linear_model, edges, times)
    predicted_linear = linear_model(edges, *linear_params)

    # Fit the linearithmic model
    linlog_params, _ = curve_fit(linearithmic_model, edges, times)
    predicted_linlog = linearithmic_model(edges, *linlog_params)

    # Plotting the results
    plt.figure(figsize=(12, 8))
    plt.scatter(edges, times, color='blue', label='Measured Times')
    #plt.plot(edges, predicted_linear, color='green', label=f'Linear Model: {linear_params[0]:.2f}*E + {linear_params[1]:.2f}')
    plt.plot(edges, predicted_linlog, color='red', label=f'Linearithmic Model: {linlog_params[0]:.2f}*E*log(E+1) + {linlog_params[1]:.2f}')
    plt.xlabel('Number of Edges (E)')
    plt.ylabel('Execution Time (microseconds)')
    plt.title('Kruskal\'s Algorithm: Performance Analysis')
    plt.legend()
    plt.grid(True)
    plt.show()

    # Calculate R-squared for both models
    print("R-squared values:")
    for predictions, model, name in [(predicted_linear, linear_model, "Linear"), (predicted_linlog, linearithmic_model, "Linearithmic")]:
        residuals = times - predictions
        ss_res = np.sum(residuals**2)
        ss_tot = np.sum((times - np.mean(times))**2)
        r_squared = 1 - (ss_res / ss_tot)
        print(f"{name} Model: {r_squared:.4f}")

def main():
    # Load data from CSV
    data = pd.read_csv('output.csv')
    
    # Fitting the curve and plotting
    fit_curve_and_plot(data)

main()