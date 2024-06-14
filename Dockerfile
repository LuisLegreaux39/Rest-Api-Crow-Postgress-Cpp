FROM  conanio/gcc11-ubuntu16.04:latest
# Set the working directory to /app inside the container
WORKDIR /app
# Copy app files
COPY . .
# Install dependencies ()
CMD ["sh" ,"build.sh"]