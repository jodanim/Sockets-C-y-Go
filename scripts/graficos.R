library(ggplot2)
library(viridis)
library(nortest)

#---------------------- Cargar datos ----------------------#

#df_img_go = read.csv('../results/go/img_go_3.csv', header=T)
df_img_go = read.csv('../results/go/result_imgs.csv', header=T)
df_img_go_1M = read.csv('../results/go/img_go_1M.csv', header=T)
df_img_go_32M = read.csv('../results/go/img_go_32M.csv', header=T)

colnames(df_img_go) <- c("size.B","iter", "time.ns")
colnames(df_img_go_1M) <- c("size.B","iter", "time.ns")
colnames(df_img_go_32M) <- c("size.B","iter", "time.ns")

df_img_go.sizes <- unique(df_img_go$size.B)
df_img_go.mean <- aggregate(df_img_go[,3], list(df_img_go$size.B), mean)
colnames(df_img_go.mean) <- c("size.B", "avg.time.ns")
df_img_go.var <- aggregate(df_img_go[,3], list(df_img_go$size.B), var)
df_img_go.speed <- df_img_go.mean$size.B/ df_img_go.mean$avg.time.ns


#---------------------- Normalidad ----------------------#
qqnorm(df_img_go_1M$time.ns);qqline(df_img_go_1M$time.ns);
qqnorm(df_img_go_32M$time.ns);qqline(df_img_go_32M$time.ns);

qqnorm(df_img_go$time.ns[df_img_go$size.B == df_img_go.sizes[1]]);

shapiro.test(df_img_go$time.ns[df_img_go$size.B == df_img_go.sizes[1]])
shapiro.test(df_img_go$time.ns[df_img_go$size.B == df_img_go.sizes[2]])
shapiro.test(df_img_go$time.ns[df_img_go$size.B == df_img_go.sizes[3]])
shapiro.test(df_img_go$time.ns[df_img_go$size.B == df_img_go.sizes[4]])
shapiro.test(df_img_go$time.ns[df_img_go$size.B == df_img_go.sizes[5]])
shapiro.test(df_img_go$time.ns[df_img_go$size.B == df_img_go.sizes[6]])
shapiro.test(df_img_go$time.ns[df_img_go$size.B == df_img_go.sizes[7]])
shapiro.test(df_img_go$time.ns[df_img_go$size.B == df_img_go.sizes[8]])
shapiro.test(df_img_go$time.ns[df_img_go$size.B == df_img_go.sizes[9]])
shapiro.test(df_img_go$time.ns[df_img_go$size.B == df_img_go.sizes[10]])

#---------------------- Graficos ----------------------#



ggplot(data=df_img_go_1M, aes(x = time.ns)) + geom_histogram(bins=16, color="black", fill="white")
ggplot(data=df_img_go_32M, aes(x = time.ns)) + geom_histogram(bins=16, color="black", fill="white")

scatter <- ggplot(data=df_img_go.mean, aes(x=size.B, y = avg.time.ns))
scatter + geom_point(color="black", fill="white") + geom_smooth(method = lm, se = FALSE)

boxplot(df_img_32M$time)

boxplot(df_img_1M$time)