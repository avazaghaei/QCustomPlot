# QCustomPlot Based Qt Application with Enhanced Features
This Qt C++ application leverages the QCustomPlot library to create dynamic and interactive data visualizations. By incorporating a rich set of QCustomPlot features, including point selection, plotting, axis customization, zoom, and area selection, the application offers a robust platform for data exploration. To enhance functionality, custom modifications have been made to the QCustomPlot library, enabling precise point selection and other tailored interactions.

The application prioritizes code clarity and efficiency through the exclusive use of code-based GUI development. This approach fosters clean code practices, increased reusability, and accelerated development cycles compared to traditional drag-and-drop design methods. However, the current fixed-size layout presents limitations that will be addressed in future iterations to explore dynamic layout solutions and provide a comprehensive comparison of different approaches.
## **Features:**
### **QCustomPlot**	
* **Data Handling:**

    * Generate random data: Create synthetic data for testing and visualization purposes.
    * Import/export data: Read data from Excel files and write plot data to Excel format.

* **Plot Customization:**

    * Plot types: Support various plot types (e.g., line, scatter, bar) for diverse data representation.
    * Axis control: Customize axis scaling, tick positions, and orientation (e.g., reverse X-axis) for tailored visualizations.
    * Zoom and pan: Explore data interactively by zooming in/out and panning across the plot.
    * Area selection: Select specific regions of the plot for focused analysis.

* **User Interaction:**

    * Point selection: Precisely select data points on the plot for detailed inspection.
    * Image export: Capture the plot as an image for documentation or sharing.
    * Context menu: Access additional functionalities and options through a right-click menu.

* **Additional Features:**

    * Custom QCustomPlot modifications: Enhancements to the underlying library for specialized visualizations or performance optimizations.

### **Code-Based GUI Development Advantages**
* **Flexibility and customization:**

	* Easily modify and adapt the GUI to meet changing requirements without being constrained by visual design tools.
	
* **Reusability:**

	* Create reusable UI components and design patterns that can be applied across multiple projects.
	
* **Accelerated development:**

	* Streamlined GUI development process leading to faster time-to-market.
	
* **Version control integration:**

	* Seamlessly manage GUI changes alongside code changes using version control systems.
	
## **Getting Started:**
1.Open Qt Creator: 

	Launch the Qt Creator IDE.
	
2.Open the Project:

    Go to File -> Open File or Project.
    Navigate to the project's root directory and select the .pro file.
	
3.Build the Project:

    Click on the Build button in the Qt Creator toolbar.
	
4.Run the Application:
 
    Click on the Run button in the Qt Creator toolbar.
	
**Note:** This project relies on a custom QCustomPlot build. Compatibility with standard QCustomPlot versions is not guaranteed.
	
## **Prerequisites:**
* Qt framework:
	
	* You can run the application with MSVC and MINGW kits.
	* ou can run the application in both Debug and Release mode

* Operating System:
	
	* This application is designed to be cross-platform compatible, allowing you to run it on various operating systems.

	
## **Installation:**

1. Clone the repository:
   ```bash
   git clone [https://github.com/avazaghaei/QCustomPlot](https://github.com/avazaghaei/QCustomPlot.git)
