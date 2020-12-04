# In the name of GOD

# Importing packages
library(readr) # A cool package for reading files!
library(ggplot2) # Another cool package for plots
library(ggthemes) # Themes of ggplot2
library(dplyr) # A very useful package for data transformation

# Starting with ggplot: point plot
p + geom_point()
p = ggplot(data = mtcars,aes(x = hp, y = disp))
p + geom_point() + theme_dark() # Adding some cool theme!
p + geom_point() + theme_economist() + xlab('Horse Power')+ ylab('Displacement') + ggtitle('Displacement vs Horse Power') # Labels
p + geom_point(size = 4,alpha = 0.1,color = 'blue')
p + geom_point(aes(size = mpg),alpha = 0.6,color = 'blue')
p + geom_point(aes(size = mpg, color = gear),alpha = 0.6)
# What do we understand from these plots?

# Histograms
ggplot(data = mtcars,aes(x = qsec)) + geom_histogram(binwidth = 5,fill = "red",alpha = 0.7) # We can Change Bin Width!

# Changing coordinate!
ggplot(data = mtcars,aes(x = qsec)) + geom_histogram(binwidth = 3,fill = "red",alpha = 0.7) + scale_y_reverse() # We can Change Bin Width!

# Box plot
mtcars$gear = as.factor(mtcars$gear)
ggplot(data = mtcars,aes(x = gear,y = qsec)) + geom_boxplot()



# Reading Data
aqi = read_csv("~/Statistics-98/daily_aqi_by_county_2019.csv")
# Let's explore data!
View(aqi)
summary(aqi)
unique(aqi$`State Name`)
unique(aqi$Category)

# Let's visualize some important apsects of our data.


