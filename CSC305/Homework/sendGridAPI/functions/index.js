const functions = require("firebase-functions");
const sgMail = require("@sendgrid/mail");

let SENDGRID_API_KEY = "";
sgMail.setApiKey(SENDGRID_API_KEY);

exports.sendEmailToUser = functions.https.onRequest((request, response) => {
    const msg = {
        to: request.body.to,
        from: "ethan.demelo@uri.edu",
        subject: request.body.subject,
        text: request.body.text,
    };
    
    sgMail
        .send(msg) // This will send the message
        .then((sendGridResponse) => {
            // Here we are printing the response status code and headers
            console.log(sendGridResponse[0].statusCode);
            console.log(sendGridResponse[0].headers);
            // Once Sendgrid successfully sends the email, we are sending a response back
            // saying it was successful
            response.send("Cloud Function: Email successfully sent using Sendgrid!");
        })

        // If there was an error, we'll catch it and throw an error
        .catch((error) => {
            // Here we're handling the error by printing to console and throwing a
            // Firebase Cloud Functions HTTP error
            console.error("Unable to send email. Error: " + error);
            throw new functions.https.HttpsError("aborted", "Unable to send email.");
        });
    });