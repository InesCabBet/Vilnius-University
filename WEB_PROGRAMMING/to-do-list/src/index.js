import './style.css';
import { format, isToday, isThisWeek, parseISO } from 'date-fns';

// Task Class
class Task {
    constructor(title, description, dueDate, priority, project) {
        this.id = Date.now().toString();
        this.title = title;
        this.description = description;
        this.dueDate = dueDate;
        this.priority = priority;
        this.project = project;
        this.completed = false;
    }

    toggleComplete() {
        this.completed = !this.completed;
    }
}

// Project Class
class Project {
    constructor(name) {
        this.id = Date.now().toString();
        this.name = name;
        this.tasks = [];
    }

    addTask(task) {
        this.tasks.push(task);
    }

    removeTask(taskId) {
        this.tasks = this.tasks.filter(task => task.id !== taskId);
    }

    getTask(taskId) {
        return this.tasks.find(task => task.id === taskId);
    }
}

// TodoList Manager
class TodoList {
    constructor() {
        this.projects = [];
        this.currentProject = 'inbox';
        this.currentEditingTask = null;
        this.loadFromLocalStorage();
        this.init();
    }

    init() {
        // Si no hay proyectos, crear el proyecto Inbox por defecto
        if (this.projects.length === 0) {
            this.addProject('Inbox');
        }

        this.setupEventListeners();
        this.render();
    }

    // Local Storage
    saveToLocalStorage() {
        localStorage.setItem('todoList', JSON.stringify(this.projects));
    }

    loadFromLocalStorage() {
        const data = localStorage.getItem('todoList');
        if (data) {
            const parsed = JSON.parse(data);
            this.projects = parsed.map(p => {
                const project = new Project(p.name);
                project.id = p.id;
                project.tasks = p.tasks.map(t => {
                    const task = new Task(t.title, t.description, t.dueDate, t.priority, t.project);
                    task.id = t.id;
                    task.completed = t.completed;
                    return task;
                });
                return project;
            });
        }
    }

    // Project Management
    addProject(name) {
        const project = new Project(name);
        this.projects.push(project);
        this.saveToLocalStorage();
        return project;
    }

    removeProject(projectId) {
        this.projects = this.projects.filter(p => p.id !== projectId);
        if (this.currentProject === projectId) {
            this.currentProject = 'inbox';
        }
        this.saveToLocalStorage();
    }

    getProject(projectId) {
        return this.projects.find(p => p.id === projectId);
    }

    // Task Management
    addTask(title, description, dueDate, priority, projectId) {
        const task = new Task(title, description, dueDate, priority, projectId);
        const project = this.getProject(projectId);
        if (project) {
            project.addTask(task);
            this.saveToLocalStorage();
        }
    }

    updateTask(taskId, projectId, updates) {
        const project = this.getProject(projectId);
        if (project) {
            const task = project.getTask(taskId);
            if (task) {
                Object.assign(task, updates);
                this.saveToLocalStorage();
            }
        }
    }

    removeTask(taskId, projectId) {
        const project = this.getProject(projectId);
        if (project) {
            project.removeTask(taskId);
            this.saveToLocalStorage();
        }
    }

    toggleTaskComplete(taskId, projectId) {
        const project = this.getProject(projectId);
        if (project) {
            const task = project.getTask(taskId);
            if (task) {
                task.toggleComplete();
                this.saveToLocalStorage();
            }
        }
    }

    // Get filtered tasks
    getTasks() {
        const allTasks = this.projects.flatMap(project => 
            project.tasks.map(task => ({ ...task, projectName: project.name }))
        );

        switch (this.currentProject) {
            case 'inbox':
                const inboxProject = this.projects.find(p => p.name === 'Inbox');
                return inboxProject ? inboxProject.tasks.map(task => ({ ...task, projectName: 'Inbox' })) : [];
            case 'today':
                return allTasks.filter(task => isToday(parseISO(task.dueDate)));
            case 'week':
                return allTasks.filter(task => isThisWeek(parseISO(task.dueDate), { weekStartsOn: 1 }));
            default:
                const project = this.getProject(this.currentProject);
                return project ? project.tasks.map(task => ({ ...task, projectName: project.name })) : [];
        }
    }

    // Event Listeners
    setupEventListeners() {
        // Navigation
        document.querySelectorAll('.nav-btn').forEach(btn => {
            btn.addEventListener('click', (e) => {
                this.currentProject = e.target.dataset.project;
                this.render();
            });
        });

        // Add task button
        document.getElementById('add-task-btn').addEventListener('click', () => {
            this.openTaskModal();
        });

        // Add project button
        document.getElementById('add-project-btn').addEventListener('click', () => {
            this.openProjectModal();
        });

        // Task modal
        const taskModal = document.getElementById('task-modal');
        const taskForm = document.getElementById('task-form');
        const closeTaskModal = taskModal.querySelector('.close');
        const cancelTask = document.getElementById('cancel-task');

        closeTaskModal.addEventListener('click', () => this.closeTaskModal());
        cancelTask.addEventListener('click', () => this.closeTaskModal());
        
        taskModal.addEventListener('click', (e) => {
            if (e.target === taskModal) {
                this.closeTaskModal();
            }
        });

        taskForm.addEventListener('submit', (e) => {
            e.preventDefault();
            this.handleTaskSubmit();
        });

        // Project modal
        const projectModal = document.getElementById('project-modal');
        const projectForm = document.getElementById('project-form');
        const closeProjectModal = projectModal.querySelector('.close');
        const cancelProject = document.getElementById('cancel-project');

        closeProjectModal.addEventListener('click', () => this.closeProjectModal());
        cancelProject.addEventListener('click', () => this.closeProjectModal());
        
        projectModal.addEventListener('click', (e) => {
            if (e.target === projectModal) {
                this.closeProjectModal();
            }
        });

        projectForm.addEventListener('submit', (e) => {
            e.preventDefault();
            this.handleProjectSubmit();
        });
    }

    // Modal handlers
    openTaskModal(task = null) {
        const modal = document.getElementById('task-modal');
        const form = document.getElementById('task-form');
        const modalTitle = document.getElementById('modal-title');

        if (task) {
            // Edit mode
            modalTitle.textContent = 'Edit Task';
            document.getElementById('task-title').value = task.title;
            document.getElementById('task-description').value = task.description;
            document.getElementById('task-duedate').value = task.dueDate;
            document.getElementById('task-priority').value = task.priority;
            document.getElementById('task-project').value = task.project;
            this.currentEditingTask = task;
        } else {
            // Add mode
            modalTitle.textContent = 'Add Task';
            form.reset();
            this.currentEditingTask = null;
            
            // Set default project
            const projectSelect = document.getElementById('task-project');
            if (this.currentProject !== 'today' && this.currentProject !== 'week') {
                projectSelect.value = this.currentProject;
            }
        }

        // Populate project select
        this.populateProjectSelect();
        
        modal.classList.add('show');
    }

    closeTaskModal() {
        const modal = document.getElementById('task-modal');
        modal.classList.remove('show');
        this.currentEditingTask = null;
    }

    handleTaskSubmit() {
        const title = document.getElementById('task-title').value;
        const description = document.getElementById('task-description').value;
        const dueDate = document.getElementById('task-duedate').value;
        const priority = document.getElementById('task-priority').value;
        const projectId = document.getElementById('task-project').value;

        if (this.currentEditingTask) {
            // Update existing task
            this.updateTask(this.currentEditingTask.id, this.currentEditingTask.project, {
                title,
                description,
                dueDate,
                priority,
                project: projectId
            });
        } else {
            // Add new task
            this.addTask(title, description, dueDate, priority, projectId);
        }

        this.closeTaskModal();
        this.render();
    }

    openProjectModal() {
        const modal = document.getElementById('project-modal');
        const form = document.getElementById('project-form');
        form.reset();
        modal.classList.add('show');
    }

    closeProjectModal() {
        const modal = document.getElementById('project-modal');
        modal.classList.remove('show');
    }

    handleProjectSubmit() {
        const name = document.getElementById('project-name').value;
        this.addProject(name);
        this.closeProjectModal();
        this.render();
    }

    populateProjectSelect() {
        const select = document.getElementById('task-project');
        select.innerHTML = '';
        
        this.projects.forEach(project => {
            const option = document.createElement('option');
            option.value = project.id;
            option.textContent = project.name;
            select.appendChild(option);
        });
    }

    // Render
    render() {
        this.renderNavigation();
        this.renderTasks();
        this.renderProjectTitle();
    }

    renderNavigation() {
        // Update active nav button
        document.querySelectorAll('.nav-btn').forEach(btn => {
            btn.classList.remove('active');
            if (btn.dataset.project === this.currentProject) {
                btn.classList.add('active');
            }
        });

        // Render custom projects
        const projectsList = document.getElementById('projects-list');
        projectsList.innerHTML = '';

        this.projects.forEach(project => {
            if (project.name !== 'Inbox') {
                const projectItem = document.createElement('div');
                projectItem.className = 'project-item';
                if (this.currentProject === project.id) {
                    projectItem.classList.add('active');
                }

                projectItem.innerHTML = `
                    <span>${project.name}</span>
                    <button class="delete-project" data-project-id="${project.id}">×</button>
                `;

                projectItem.addEventListener('click', (e) => {
                    if (!e.target.classList.contains('delete-project')) {
                        this.currentProject = project.id;
                        this.render();
                    }
                });

                const deleteBtn = projectItem.querySelector('.delete-project');
                deleteBtn.addEventListener('click', () => {
                    if (confirm(`Delete project "${project.name}"?`)) {
                        this.removeProject(project.id);
                        this.render();
                    }
                });

                projectsList.appendChild(projectItem);
            }
        });
    }

    renderTasks() {
        const tasksList = document.getElementById('tasks-list');
        const tasks = this.getTasks();

        tasksList.innerHTML = '';

        if (tasks.length === 0) {
            tasksList.innerHTML = '<p style="color: #7f8c8d; text-align: center; padding: 40px;">No tasks yet. Add one!</p>';
            return;
        }

        tasks.forEach(task => {
            const taskItem = document.createElement('div');
            taskItem.className = `task-item priority-${task.priority}`;
            if (task.completed) {
                taskItem.classList.add('completed');
            }

            const formattedDate = format(parseISO(task.dueDate), 'MMM dd, yyyy');

            taskItem.innerHTML = `
                <input type="checkbox" class="task-checkbox" ${task.completed ? 'checked' : ''}>
                <div class="task-content">
                    <h3>${task.title}</h3>
                    ${task.description ? `<p>${task.description}</p>` : ''}
                    <div class="task-meta">
                        <span>📅 ${formattedDate}</span>
                        <span>🏷️ ${task.priority}</span>
                        ${this.currentProject === 'today' || this.currentProject === 'week' ? `<span>📁 ${task.projectName}</span>` : ''}
                    </div>
                </div>
                <div class="task-actions">
                    <button class="btn-icon edit-task">✏️</button>
                    <button class="btn-icon delete delete-task">🗑️</button>
                </div>
            `;

            // Checkbox handler
            const checkbox = taskItem.querySelector('.task-checkbox');
            checkbox.addEventListener('change', () => {
                this.toggleTaskComplete(task.id, task.project);
                this.render();
            });

            // Edit button handler
            const editBtn = taskItem.querySelector('.edit-task');
            editBtn.addEventListener('click', () => {
                this.openTaskModal(task);
            });

            // Delete button handler
            const deleteBtn = taskItem.querySelector('.delete-task');
            deleteBtn.addEventListener('click', () => {
                if (confirm('Delete this task?')) {
                    this.removeTask(task.id, task.project);
                    this.render();
                }
            });

            tasksList.appendChild(taskItem);
        });
    }

    renderProjectTitle() {
        const titleElement = document.getElementById('project-title');
        
        switch (this.currentProject) {
            case 'inbox':
                titleElement.textContent = 'Inbox';
                break;
            case 'today':
                titleElement.textContent = 'Today';
                break;
            case 'week':
                titleElement.textContent = 'This Week';
                break;
            default:
                const project = this.getProject(this.currentProject);
                titleElement.textContent = project ? project.name : 'Unknown';
        }
    }
}

// Initialize app
const app = new TodoList();