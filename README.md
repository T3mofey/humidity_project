Analyzed a correlation between absolute humidity and temperature, using OrangePi board.

Used a ready-to-go C-program and adapted it to our task, in order to get the temperature and relative humidity values in the room. Needed to have a special conditions, so the experiment was made with an opened window during rain or snowfall. Only upon meeting requirments, we utilized our sensor. Consequently, we received temperature and relative humidity values every 10 seconds for 30 minutes.

Data analysis was made in Python using Pandas and Numpy. Knowing how the Mole diagram looks like, we estimated different formulas using mean squared error. The best correlation(with the least loss) was linear. Made a 3D diagram using matplotlib of the final formula:
y = 0.071*T + 0.231*x - 1.981               , where T stands for temperature; x stands for relative humidity
Diagram:
![image](https://github.com/user-attachments/assets/33e813a1-61e0-4edc-8ace-afb4fdee3df2)
