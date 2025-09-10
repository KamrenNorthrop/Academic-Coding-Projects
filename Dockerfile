#Base image JDK
FROM openjdk:17-jdk-alpine

# Docker image working directory
WORKDIR /app

# Jar file from mvn
COPY target/D387_sample_code-0.0.2-SNAPSHOT.jar app.jar

# Accesibility to 8080
EXPOSE 8080

# Run commands
ENTRYPOINT ["java", "-jar", "app.jar"]