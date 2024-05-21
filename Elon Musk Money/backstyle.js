
let wealthHeading = document.getElementById("wealthHeading");
let FerrariBox = document.getElementById("FerrariBox");
let HeliBox = document.getElementById("HeliBox");
let LamboBox = document.getElementById("LamboBox");
let MansionBox = document.getElementById("MansionBox");
let JetBox = document.getElementById("JetBox");
let YatchBox = document.getElementById("YatchBox");
let yourItems = document.getElementById("yourItems");
let returnItems = document.getElementById("returnItems");
let Helireceipt = document.getElementById("Helireceipt");
let Ferrarireceipt = document.getElementById("Ferrarireceipt");
let Lamboreceipt = document.getElementById("Lamboreceipt");
let Mansionreceipt = document.getElementById("Mansionreceipt");
let Jetreceipt = document.getElementById("Jetreceipt");
let Yatchreceipt = document.getElementById("Yatchreceipt");
let totalBill = document.getElementById("totalBill");


const buttonSound = new Audio("Assets/Money.MP3");

document.addEventListener("DOMContentLoaded", function() {
    const button = document.getElementById("HeliPurchase");
    button.addEventListener("click", playSound);
});

function playSound() {
    buttonSound.play();
}


function updateTotalBill() {
    let heliCost = parseFloat(Helireceipt.textContent.replace(/[^\d.-]/g, "")) || 0;
    let ferrariCost = parseFloat(Ferrarireceipt.textContent.replace(/[^\d.-]/g, "")) || 0;
    let lamboCost = parseFloat(Lamboreceipt.textContent.replace(/[^\d.-]/g, "")) || 0;
    let mansionCost = parseFloat(Mansionreceipt.textContent.replace(/[^\d.-]/g, "")) || 0;
    let jetCost = parseFloat(Jetreceipt.textContent.replace(/[^\d.-]/g, "")) || 0;
    let yatchCost = parseFloat(Yatchreceipt.textContent.replace(/[^\d.-]/g, "")) || 0;
    
    let totalCost = heliCost + ferrariCost + lamboCost + mansionCost + jetCost + yatchCost;
    totalBill.textContent = `Total Bill: $${totalCost.toLocaleString()}`;
}

function heliPurchased() {
    let currentWealthText = wealthHeading.textContent;
    let currentWealth = parseFloat(currentWealthText.replace(/[^\d.-]/g, ""));
    let numberOfHeli = parseInt(HeliBox.value);
    let costPerHeli = 2000000;
    let totalCost = numberOfHeli * costPerHeli;
    let newWealth = currentWealth - totalCost;
    wealthHeading.textContent = `Elon Musk's Wealth: $${newWealth}`;
    yourItems.textContent = `Congratulations! You now own: ${numberOfHeli} Helicopter${numberOfHeli > 1 ? 's' : ''}.`;
    Helireceipt.textContent = `* ${numberOfHeli} Helicopter${numberOfHeli > 1 ? 's' : ''} = $${totalCost}`;
    updateTotalBill();
}

function HeliSelled() {
    let currentWealthText = wealthHeading.textContent;
    let currentWealth = parseFloat(currentWealthText.replace(/[^\d.-]/g, ""));
    let numberOfHeli = parseInt(HeliBox.value);
    let costPerHeli = 2000000;
    let totalCost = numberOfHeli * costPerHeli;
    let newWealth = currentWealth + totalCost;
    wealthHeading.textContent = `Elon Musk's Wealth: $${newWealth}`;
    returnItems.textContent = `Congratulations! You sold: ${numberOfHeli} Helicopter${numberOfHeli > 1 ? 's' : ''}.`;
    Helireceipt.textContent = `* 0 Helicopter = $0`;
    updateTotalBill();
}

function ferrariPurchased() {
    let currentWealthText = wealthHeading.textContent;
    let currentWealth = parseFloat(currentWealthText.replace(/[^\d.-]/g, ""));
    let numberOfFerraris = parseInt(FerrariBox.value);
    let costPerFerrari = 1500000;
    let totalCost = numberOfFerraris * costPerFerrari;
    let newWealth = currentWealth - totalCost;
    wealthHeading.textContent = `Elon Musk's Wealth: $${newWealth}`;
    yourItems.textContent = `Congratulations! You now own: ${numberOfFerraris} Ferrari${numberOfFerraris > 1 ? 's' : ''}.`;
    Ferrarireceipt.textContent = `* ${numberOfFerraris} Ferrari${numberOfFerraris > 1 ? 's' : ''} = $${totalCost}`;
    updateTotalBill();
}

function ferrariSelled() {
    let currentWealthText = wealthHeading.textContent;
    let currentWealth = parseFloat(currentWealthText.replace(/[^\d.-]/g, ""));
    let numberOfFerraris = parseInt(FerrariBox.value);
    let costPerFerrari = 1500000;
    let totalCost = numberOfFerraris * costPerFerrari;
    let newWealth = currentWealth + totalCost;
    wealthHeading.textContent = `Elon Musk's Wealth: $${newWealth}`;
    returnItems.textContent = `Congratulations! You sold: ${numberOfFerraris} Ferrari${numberOfFerraris > 1 ? 's' : ''}.`;
    Ferrarireceipt.textContent = `* 0 Ferrari = $0`;
    updateTotalBill();
}

function lamboPurchased() {
    
    let currentWealthText = wealthHeading.textContent;
    let currentWealth = parseFloat(currentWealthText.replace(/[^\d.-]/g, ""));
    let numberOfLambos = parseInt(LamboBox.value);
    let costPerLambo = 400000;
    let totalCost = numberOfLambos * costPerLambo;
    let newWealth = currentWealth - totalCost;
    wealthHeading.textContent = `Elon Musk's Wealth: $${newWealth}`;
    yourItems.textContent = `Congratulations! You now own: ${numberOfLambos} Lamborghini${numberOfLambos > 1 ? 's' : ''}.`;
    Lamboreceipt.textContent = `* ${numberOfLambos} Lamborghini${numberOfLambos > 1 ? 's' : ''} = $${totalCost}`;
    updateTotalBill();
}

function lamboSelled() {
    let currentWealthText = wealthHeading.textContent;
    let currentWealth = parseFloat(currentWealthText.replace(/[^\d.-]/g, ""));
    let numberOfLambos = parseInt(LamboBox.value);
    let costPerLambo = 400000;
    let totalCost = numberOfLambos * costPerLambo;
    let newWealth = currentWealth + totalCost;
    wealthHeading.textContent = `Elon Musk's Wealth: $${newWealth}`;
    returnItems.textContent = `Congratulations! You sold: ${numberOfLambos} Lamborghini${numberOfLambos > 1 ? 's' : ''}.`;
    Lamboreceipt.textContent = `* 0 Lamborghini = $0`;
    updateTotalBill();
}

function mansionPurchased() {
    let currentWealthText = wealthHeading.textContent;
    let currentWealth = parseFloat(currentWealthText.replace(/[^\d.-]/g, ""));
    let numberOfMansions = parseInt(MansionBox.value);
    let costPerMansion = 10000000;
    let totalCost = numberOfMansions * costPerMansion;
    let newWealth = currentWealth - totalCost;
    wealthHeading.textContent = `Elon Musk's Wealth: $${newWealth}`;
    yourItems.textContent = `Congratulations! You now own: ${numberOfMansions} Mansion${numberOfMansions > 1 ? 's' : ''}.`;
    Mansionreceipt.textContent = `* ${numberOfMansions} Mansion${numberOfMansions > 1 ? 's' : ''} = $${totalCost}`;
    updateTotalBill();
}

function MansionSelled() {
    let currentWealthText = wealthHeading.textContent;
    let currentWealth = parseFloat(currentWealthText.replace(/[^\d.-]/g, ""));
    let numberOfMansions = parseInt(MansionBox.value);
    let costPerMansion = 10000000;
    let totalCost = numberOfMansions * costPerMansion;
    let newWealth = currentWealth + totalCost;
    wealthHeading.textContent = `Elon Musk's Wealth: $${newWealth}`;
    returnItems.textContent = `Congratulations! You sold: ${numberOfMansions} Mansion${numberOfMansions > 1 ? 's' : ''}.`;
    Mansionreceipt.textContent = `* 0 Mansion = $0`;
    updateTotalBill();
}

function jetPurchased() {
    let currentWealthText = wealthHeading.textContent;
    let currentWealth = parseFloat(currentWealthText.replace(/[^\d.-]/g, ""));
    let numberOfJets = parseInt(JetBox.value);
    let costPerJet = 20000000;
    let totalCost = numberOfJets * costPerJet;
    let newWealth = currentWealth - totalCost;
    wealthHeading.textContent = `Elon Musk's Wealth: $${newWealth}`;
    yourItems.textContent = `Congratulations! You now own: ${numberOfJets} Jet${numberOfJets > 1 ? 's' : ''}.`;
    Jetreceipt.textContent = `* ${numberOfJets} Jet${numberOfJets > 1 ? 's' : ''} = $${totalCost}`;
    updateTotalBill();
}

function JetSelled() {
    let currentWealthText = wealthHeading.textContent;
    let currentWealth = parseFloat(currentWealthText.replace(/[^\d.-]/g, ""));
    let numberOfJets = parseInt(JetBox.value);
    let costPerJet = 20000000;
    let totalCost = numberOfJets * costPerJet;
    let newWealth = currentWealth + totalCost;
    wealthHeading.textContent = `Elon Musk's Wealth: $${newWealth}`;
    returnItems.textContent = `Congratulations! You sold: ${numberOfJets} Jet${numberOfJets > 1 ? 's' : ''}.`;
    Jetreceipt.textContent = `* 0 Jet = $0`;
    updateTotalBill();
}

function yatchPurchased() {
    let currentWealthText = wealthHeading.textContent;
    let currentWealth = parseFloat(currentWealthText.replace(/[^\d.-]/g, ""));
    let numberOfYatchs = parseInt(YatchBox.value);
    let costPerYatch = 50000000;
    let totalCost = numberOfYatchs * costPerYatch;
    let newWealth = currentWealth - totalCost;
    wealthHeading.textContent = `Elon Musk's Wealth: $${newWealth}`;
    yourItems.textContent = `Congratulations! You now own: ${numberOfYatchs} Yatch${numberOfYatchs > 1 ? 's' : ''}.`;
    Yatchreceipt.textContent = `* ${numberOfYatchs} Yatch${numberOfYatchs > 1 ? 's' : ''} = $${totalCost}`;
    updateTotalBill();
}

function yatchSelled() {
    let currentWealthText = wealthHeading.textContent;
    let currentWealth = parseFloat(currentWealthText.replace(/[^\d.-]/g, ""));
    let numberOfYatchs = parseInt(YatchBox.value);
    let costPerYatch = 50000000;
    let totalCost = numberOfYatchs * costPerYatch;
    let newWealth = currentWealth + totalCost;
    wealthHeading.textContent = `Elon Musk's Wealth: $${newWealth}`;
    returnItems.textContent = `Congratulations! You sold: ${numberOfYatchs} Yatch${numberOfYatchs > 1 ? 's' : ''}.`;
    Yatchreceipt.textContent = `* 0 Yatch = $0`;
    updateTotalBill();
}
