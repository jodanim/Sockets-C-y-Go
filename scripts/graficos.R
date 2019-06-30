library(ggplot2)
library(viridis)
library(nortest)

#---------------------- datos de prueba (ignorar) ----------------------#

#df_img_go = read.csv('../results/go/result_imgs.csv', header=T)

df_img_go = read.csv('../results/go/img_go_3.csv', header=T)
colnames(df_img_go) <- c("size.B","iter", "time.ns")

df_img_go_1M = read.csv('../results/go/img_go_1M.csv', header=T)
colnames(df_img_go_1M) <- c("size.B","iter", "time.ns")


df = read.csv('../results/go_32M_txt.csv', header=T)
colnames(df) <- c("size.B","iter", "time.ns")

#---------------------- Cargar datos ----------------------#

df_txt_go_32M = read.csv('../results/normal/go_32M_txt.csv', header=T)
colnames(df_txt_go_32M) <- c("size.B","iter", "time.ns")
df_img_go_32M = read.csv('../results/normal/go_32M_jpg_3.csv', header=T)
colnames(df_img_go_32M) <- c("size.B","iter", "time.ns")
df_webm_go_32M = read.csv('../results/normal/go_32M_webm_7.csv', header=T)
colnames(df_webm_go_32M) <- c("size.B","iter", "time.ns")

df_txt_go_32M$vel = df_txt_go_32M$size.B/ (df_txt_go_32M$time.ns / 10^9) / 1024
df_img_go_32M$vel = df_img_go_32M$size.B/ (df_img_go_32M$time.ns / 10^9) / 1024
df_webm_go_32M$vel = df_webm_go_32M$size.B/ (df_webm_go_32M$time.ns / 10^9) / 1024

#---------------------- Ignorar ----------------------#
df_img_go.sizes <- unique(df_img_go$size.B)
df_img_go.mean <- aggregate(df_img_go[,3], list(df_img_go$size.B), mean)
colnames(df_img_go.mean) <- c("size.B", "avg.time.ns")
df_img_go.var <- aggregate(df_img_go[,3], list(df_img_go$size.B), var)
df_img_go.speed <- df_img_go.mean$size.B/ df_img_go.mean$avg.time.ns


#---------------------- Normalidad ----------------------#
qqnorm(df_txt_go_32M$vel);qqline(df_txt_go_32M$vel);
qqnorm(df_img_go_32M$vel);qqline(df_img_go_32M$vel);
qqnorm(df_webm_go_32M$vel);qqline(df_webm_go_32M$vel);

shapiro.test(df_txt_go_32M$vel)$p.value
ad.test(df_txt_go_32M$vel)$p.value

shapiro.test(df_img_go_32M$vel)$p.value
ad.test(df_img_go_32M$vel)$p.value

shapiro.test(df_webm_go_32M$vel)$p.value
ad.test(df_webm_go_32M$vel)$p.value


mean(df_txt_go_32M$vel)
mean(df_img_go_32M$vel)
mean(df_webm_go_32M$vel)
sd(df_txt_go_32M$vel)
sd(df_img_go_32M$vel)
sd(df_webm_go_32M$vel)

#---------------------- Pruebas de Hipotesis ----------------------#
# Queremos determinar si las velocidades tienen la misma distribución
# independientemente del tipo de archivo. Usamos Kolmogorov-Smirnov
# y buscamos que el p-value sea > 0.05

ks.test(df_txt_go_32M$vel, df_webm_go_32M$vel)
ks.test(df_img_go_32M$vel, df_webm_go_32M$vel)
ks.test(df_img_go_32M$vel, df_txt_go_32M$vel)

#---------------------- Graficos ----------------------#
ggplot(data=df_txt_go_32M, aes(x=vel)) +
  geom_histogram(bins = 12, color = "#bd4a86", fill = "#ddb3ca") +
  scale_x_continuous(name = "Velocidad de descarga (KB/s)")
ggplot(data=df_img_go_32M, aes(x=vel)) +
  geom_histogram(bins = 12, color = "#07070a", fill = "#a3a3a4") +
  scale_x_continuous(name = "Velocidad de descarga (KB/s)")
ggplot(data=df_webm_go_32M, aes(x=vel)) +
  geom_histogram(bins = 12, color = "#e3dab2", fill = "#f4f4e1") +
  scale_x_continuous(name = "Velocidad de descarga (KB/s)")


vels <- data.frame(
  File.type = factor( rep(c('txt', 'jpg', 'webm'), c(length(df_txt_go_32M$vel), length(df_img_go_32M$vel), length(df_webm_go_32M$vel))) ),
  Vel.KB.s = c(df_txt_go_32M$vel, df_img_go_32M$vel, df_webm_go_32M$vel)
)

ggplot(data=vels, aes(x = Vel.KB.s, color = File.type, fill = File.type)) +
  geom_histogram(aes(y = ..density..), bins=15, alpha = 0.10, position = "identity") +
  geom_density(alpha = 0.25) +
  scale_color_viridis(discrete = TRUE, option = "A") +
  scale_fill_viridis(discrete = TRUE, option = "A") 


#---------------------- Ignorar ----------------------#
df_img_go_32M$time.ns/10^9

scatter <- ggplot(data=df_img_go.mean, aes(x=size.B, y = avg.time.ns))
scatter + geom_point(color="black", fill="white") + geom_smooth(method = lm, se = FALSE)

boxplot(df_img_go_32M$time)

boxplot(df_img_1M$time)