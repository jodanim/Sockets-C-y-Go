library(ggplot2)

df1 = read.csv('./65536B.csv', header=T)

df1 = as.data.frame(df1)
colnames(df1) <- c("size","time")

ggplot(data=df1, aes(x = time)) + geom_histogram(binwidth = 45000, color="black", fill="white")


df2 = read.csv('./131072B.csv', header=T)

df2 = as.data.frame(df2)
colnames(df2) <- c("size","time")


ggplot(data=df2, aes(x = time)) + geom_histogram(binwidth = 450000)

boxplot(df2)