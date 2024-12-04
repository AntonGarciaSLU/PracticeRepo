#!/bin/bash
# Example for deploying to a server
echo "Deploying application..."
scp -r ./build user@your-server:/var/www/html
