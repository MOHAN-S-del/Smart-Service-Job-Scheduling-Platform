// script.js
// Smart Service Job Scheduling Platform - DAA Project
// JavaScript for UI Simulation (No Backend Connection)

/**
 * GREEDY ALGORITHM SIMULATION:
 * 
 * The backend C++ code implements greedy job scheduling that selects
 * workers based on:
 * 1. Highest rating (quality)
 * 2. Minimum distance (efficiency)
 * 3. Available capacity (feasibility)
 * 
 * This JavaScript simulates the result of that greedy algorithm
 * for demonstration purposes in college presentations.
 */

// ========================================
// WORKER DATABASE (Simulated Backend Data)
// ========================================

const workerDatabase = {
    "plumber": [
        { id: 1, name: "Rajesh Kumar", rating: 4.8, distance: 2.5, capacity: 3, currentLoad: 1 },
        { id: 2, name: "Amit Sharma", rating: 4.5, distance: 4.2, capacity: 5, currentLoad: 2 },
        { id: 3, name: "Suresh Patel", rating: 4.9, distance: 3.1, capacity: 4, currentLoad: 0 }
    ],
    "electrician": [
        { id: 4, name: "Vikas Singh", rating: 4.7, distance: 1.8, capacity: 4, currentLoad: 1 },
        { id: 5, name: "Manoj Verma", rating: 4.6, distance: 3.5, capacity: 3, currentLoad: 2 },
        { id: 6, name: "Ravi Gupta", rating: 4.9, distance: 2.2, capacity: 5, currentLoad: 1 }
    ],
    "carpenter": [
        { id: 7, name: "Anil Yadav", rating: 4.5, distance: 3.8, capacity: 3, currentLoad: 0 },
        { id: 8, name: "Deepak Joshi", rating: 4.8, distance: 2.1, capacity: 4, currentLoad: 1 },
        { id: 9, name: "Ramesh Tiwari", rating: 4.6, distance: 4.5, capacity: 5, currentLoad: 3 }
    ],
    "painter": [
        { id: 10, name: "Sanjay Mishra", rating: 4.7, distance: 2.9, capacity: 4, currentLoad: 2 },
        { id: 11, name: "Prakash Reddy", rating: 4.9, distance: 1.5, capacity: 3, currentLoad: 0 },
        { id: 12, name: "Ashok Nair", rating: 4.4, distance: 3.7, capacity: 5, currentLoad: 1 }
    ],
    "cleaner": [
        { id: 13, name: "Mohan Das", rating: 4.6, distance: 2.3, capacity: 6, currentLoad: 2 },
        { id: 14, name: "Gopal Singh", rating: 4.8, distance: 1.9, capacity: 5, currentLoad: 1 },
        { id: 15, name: "Krishna Kumar", rating: 4.5, distance: 3.2, capacity: 4, currentLoad: 0 }
    ]
};

// ========================================
// GREEDY ALGORITHM IMPLEMENTATION
// ========================================

/**
 * Greedy Job Scheduling Algorithm (Simulated)
 * 
 * STRATEGY:
 * 1. Filter workers who have available capacity
 * 2. Sort by rating (descending) - Quality first
 * 3. If ratings are equal, sort by distance (ascending) - Efficiency
 * 4. Select the top worker (Greedy Choice)
 * 
 * TIME COMPLEXITY: O(n log n) due to sorting
 * where n = number of available workers for the service
 * 
 * @param {string} serviceType - Type of service requested
 * @return {object} - Selected worker or null
 */
function greedyScheduleJob(serviceType) {
    // Get all workers for this service type
    const workers = workerDatabase[serviceType];
    
    if (!workers || workers.length === 0) {
        return null;
    }
    
    // Step 1: Filter workers with available capacity
    const availableWorkers = workers.filter(function(worker) {
        return worker.currentLoad < worker.capacity;
    });
    
    // Check if any workers are available
    if (availableWorkers.length === 0) {
        return null;
    }
    
    // Step 2: Sort using Greedy criteria
    // Primary: Rating (descending - higher is better)
    // Secondary: Distance (ascending - closer is better)
    availableWorkers.sort(function(a, b) {
        // Compare ratings first (higher rating preferred)
        if (a.rating !== b.rating) {
            return b.rating - a.rating; // Descending order
        }
        // If ratings equal, compare distance (shorter distance preferred)
        return a.distance - b.distance; // Ascending order
    });
    
    // Step 3: Select the best worker (Greedy Choice)
    const selectedWorker = availableWorkers[0];
    
    return selectedWorker;
}

// ========================================
// DEADLINE CALCULATION
// ========================================

/**
 * Calculates job deadline based on service type and worker distance
 * 
 * @param {string} serviceType - Type of service
 * @param {number} distance - Distance to worker in km
 * @return {string} - Formatted deadline
 */
function calculateDeadline(serviceType, distance) {
    const currentDate = new Date();
    
    // Base time estimate (in hours)
    const baseTime = {
        "plumber": 2,
        "electrician": 1.5,
        "carpenter": 3,
        "painter": 4,
        "cleaner": 1
    };
    
    // Travel time: 0.5 hours per km (average)
    const travelTime = distance * 0.5;
    
    // Total time = base service time + travel time
    const totalHours = baseTime[serviceType] + travelTime;
    
    // Add hours to current time
    currentDate.setHours(currentDate.getHours() + Math.ceil(totalHours));
    
    // Format: "2 Feb, 3:30 PM"
    const options = { 
        day: 'numeric', 
        month: 'short', 
        hour: 'numeric', 
        minute: '2-digit',
        hour12: true 
    };
    
    return currentDate.toLocaleString('en-US', options);
}

// ========================================
// UI INTERACTION FUNCTIONS
// ========================================

/**
 * Main function: Handles "Schedule Job" button click
 * 
 * WORKFLOW:
 * 1. Read selected service from dropdown
 * 2. Validate selection
 * 3. Apply greedy algorithm to find best worker
 * 4. Display result with worker details
 */
function scheduleJob() {
    // Get selected service type from dropdown
    const serviceSelect = document.getElementById("serviceType");
    const selectedService = serviceSelect.value;
    
    // Get result box element
    const resultBox = document.getElementById("resultBox");
    
    // Validation: Check if a service is selected
    if (selectedService === "") {
        resultBox.innerHTML = `
            <div class="info-box">
                <p>⚠️ Please select a service type first!</p>
            </div>
        `;
        return;
    }
    
    // Show loading message
    resultBox.innerHTML = `
        <p class="result-empty">🔄 Processing your request...</p>
    `;
    
    // Simulate processing delay (for realistic demo)
    setTimeout(function() {
        // Apply Greedy Algorithm
        const selectedWorker = greedyScheduleJob(selectedService);
        
        // Check if worker was found
        if (!selectedWorker) {
            resultBox.innerHTML = `
                <div class="info-box">
                    <p>❌ Sorry! All workers are currently busy. Please try again later.</p>
                </div>
            `;
            return;
        }
        
        // Calculate deadline
        const deadline = calculateDeadline(selectedService, selectedWorker.distance);
        
        // Display result
        displayResult(selectedService, selectedWorker, deadline);
        
    }, 800); // 800ms delay for demonstration
}

/**
 * Displays the scheduling result in a formatted way
 * 
 * @param {string} serviceType - Type of service
 * @param {object} worker - Selected worker object
 * @param {string} deadline - Calculated deadline
 */
function displayResult(serviceType, worker, deadline) {
    const resultBox = document.getElementById("resultBox");
    
    // Calculate load percentage
    const loadPercentage = Math.round((worker.currentLoad / worker.capacity) * 100);
    
    // Generate HTML output
    resultBox.innerHTML = `
        <div class="success-box">
            <p>✅ Job Scheduled Successfully!</p>
        </div>
        
        <h3 class="mt-20">📋 Scheduling Details</h3>
        
        <div class="info-box mt-10">
            <p><strong>Service Type:</strong> ${capitalizeFirst(serviceType)}</p>
        </div>
        
        <h3 class="mt-20">👷 Assigned Worker (Greedy Selection)</h3>
        
        <pre>
Worker ID:       ${worker.id}
Worker Name:     ${worker.name}
Rating:          ⭐ ${worker.rating}/5.0
Distance:        📍 ${worker.distance} km
Current Load:    ${worker.currentLoad}/${worker.capacity} jobs (${loadPercentage}% utilized)
Status:          ✅ Available

<strong>Greedy Criteria Used:</strong>
✓ Highest Rating: ${worker.rating}/5.0
✓ Minimum Distance: ${worker.distance} km
✓ Available Capacity: ${worker.capacity - worker.currentLoad} slots remaining
        </pre>
        
        <div class="info-box mt-20">
            <p><strong>⏰ Expected Completion:</strong> ${deadline}</p>
        </div>
        
        <p class="mt-20" style="color: #666; font-size: 13px; text-align: center;">
            <em>Algorithm: Greedy Job Scheduling (Sort by Rating & Distance)</em>
        </p>
    `;
}

/**
 * Utility function: Capitalizes first letter of a string
 * 
 * @param {string} str - Input string
 * @return {string} - Capitalized string
 */
function capitalizeFirst(str) {
    return str.charAt(0).toUpperCase() + str.slice(1);
}

// ========================================
// EVENT LISTENERS (Page Load)
// ========================================

/**
 * Initialize event listeners when page loads
 * This ensures all DOM elements are ready before attaching events
 */
window.onload = function() {
    // Get the button element
    const scheduleButton = document.getElementById("scheduleBtn");
    
    // Attach click event to button
    if (scheduleButton) {
        scheduleButton.addEventListener("click", scheduleJob);
    }
    
    // Optional: Also trigger on Enter key in dropdown
    const serviceSelect = document.getElementById("serviceType");
    if (serviceSelect) {
        serviceSelect.addEventListener("change", function() {
            // Clear previous result when selection changes
            const resultBox = document.getElementById("resultBox");
            if (resultBox && this.value === "") {
                resultBox.innerHTML = `
                    <p class="result-empty">Select a service and click "Schedule Job" to see results.</p>
                `;
            }
        });
    }
    
    console.log("✅ Job Scheduling System Initialized");
    console.log("📊 Worker Database Loaded: " + Object.keys(workerDatabase).length + " service types");
};

/**
 * ========================================
 * ALGORITHM EXPLANATION (For Viva/Demo)
 * ========================================
 * 
 * GREEDY APPROACH:
 * 1. At each scheduling request, select the "locally optimal" worker
 * 2. Criteria: Highest rating + Minimum distance
 * 3. This ensures quality service with quick response time
 * 
 * WHY GREEDY WORKS HERE:
 * - Customer satisfaction (high rating)
 * - Cost efficiency (low distance)
 * - Resource utilization (check capacity)
 * 
 * TIME COMPLEXITY:
 * - Filtering: O(n)
 * - Sorting: O(n log n)
 * - Selection: O(1)
 * - Overall: O(n log n)
 * 
 * SPACE COMPLEXITY: O(n) for filtered array
 * 
 * REAL-WORLD APPLICATIONS:
 * - Uber/Ola driver assignment
 * - Food delivery (Swiggy/Zomato)
 * - Service platforms (UrbanClap)
 * - Cloud task scheduling
 */
